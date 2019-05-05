#include "mros_topic.h"
#include "mros_memory.h"
#include "mros_list.h"
#include <stdlib.h>
#include <string.h>

using namespace mros::topic;
using namespace mros::memory;

typedef struct {
	mros_uint32					counter;
	RosTopicIdType				topic_id;
	/*
	 * topic名は，アプリケーションの subscribe, advertise の引数に渡される
	 * ROMデータを利用する．動的メモリ確保は行わない．
	 * または，mROSツールチェーン側でtopic名一覧をROM化しておき，そのデータを参照する．
	 */
	const char					*topic_name;
	mros_uint32					namelen;

	/*
	 * トピックデータ格納用キュー
	 */
	mRosSizeType				queue_maxsize;
	mRosMemoryListHeadType 		queue_head;
} RosTopicEntryType;

typedef ListEntryType(RosTopicEntryListType, RosTopicEntryType) RosTopicEntryListType;
typedef ListHeadType(RosTopicEntryListType) RosTopicEntryListHeadType;

#define ROS_TOPIC_ENTRY_INIT(entryp)	\
do {	\
	(entryp)->data.counter = 0;		\
	(entryp)->data.topic_id = MROS_ID_NONE;	\
	(entryp)->data.topic_name = NULL;	\
	(entryp)->data.namelen = 0;	\
	(entryp)->data.queue_maxsize = 1; \
} while (0)

typedef struct {
	RosTopicEntryListHeadType 	head;
	RosTopicEntryListType 		*topic_entries;
	RosTopicIdType				max_topic;
} RosTopicManagerType;

#define TOPIC_ID(index)		((index) + 1U)
#define TOPIC_INDEX(id)		((id) - 1U)


static RosTopicManagerType topic_manager;
#define TOPIC_OBJ(id)		topic_manager.topic_entries[TOPIC_INDEX((id))]


mRosReturnType RosTopic::init(mRosSizeType max_topic)
{
	topic_manager.topic_entries = (RosTopicEntryListType *)malloc(max_topic * sizeof(RosTopicEntryListType));
	//TODO ASSERT
	for (mros_uint32 i = 0; i < max_topic; i++) {
		RosTopicEntryListType *entry = &(topic_manager.topic_entries[i]);
		entry->data.topic_id = TOPIC_ID(i);
		ROS_TOPIC_ENTRY_INIT(entry);
		List_Init(&(entry->data.queue_head), mRosMemoryListEntryType, 0, NULL);
	}
	List_Init(&topic_manager.head, RosTopicEntryListType, max_topic, topic_manager.topic_entries);
	topic_manager.max_topic = max_topic;

	return MROS_E_OK;
}

mRosReturnType RosTopic::get(const char *topic_name, RosTopicIdType &id)
{
	RosTopicEntryListType *p;
	mros_uint32 len = strlen(topic_name);

	id = MROS_ID_NONE;
	ListEntry_Foreach(&topic_manager.head, p) {
		if (len != p->data.namelen) {
			continue;
		}
		if (!strcmp(p->data.topic_name, topic_name)) {
			id = p->data.topic_id;
			break;
		}
	}
	if (id == MROS_ID_NONE) {
		return MROS_E_NOENT;
	}
	return MROS_E_OK;
}

mRosReturnType RosTopic::create(const char *topic_name, RosTopicIdType &id)
{
	RosTopicEntryListType *p;
	mros_uint32 len = strlen(topic_name);

	mRosReturnType ret = RosTopic::get(topic_name, id);
	if (ret == MROS_E_OK) {
		return MROS_E_EXIST;
	}

	ListEntry_Alloc(&topic_manager.head, RosTopicEntryListType, &p);
	if (p == NULL) {
		return MROS_E_NOMEM;
	}
	p->data.counter = 1U;
	p->data.namelen = len;
	p->data.topic_name = topic_name;
	ListEntry_AddEntry(&topic_manager.head, p);
	return MROS_E_OK;
}

mRosReturnType RosTopic::create(const char *topic_name)
{
	RosTopicIdType id;
	return RosTopic::create(topic_name, id);
}
mRosReturnType RosTopic::set_quesize(const char *topic_name, mRosSizeType size)
{
	RosTopicIdType id;

	mRosReturnType ret = RosTopic::get(topic_name, id);
	if (ret != MROS_E_OK) {
		return ret;
	}
	TOPIC_OBJ(id).data.queue_maxsize = size;
	return MROS_E_OK;
}
mRosReturnType RosTopic::set_quesize(RosTopicIdType id, mRosSizeType size)
{
	if (id > topic_manager.max_topic) {
		return MROS_E_RANGE;
	}
	if (TOPIC_OBJ(id).data.counter == 0) {
		return MROS_E_INVAL;
	}
	TOPIC_OBJ(id).data.queue_maxsize = size;
	return MROS_E_OK;
}

mRosReturnType RosTopic::remove(const char *topic_name)
{
	RosTopicIdType id;

	mRosReturnType ret = RosTopic::get(topic_name, id);
	if (ret != MROS_E_OK) {
		return ret;
	}
	TOPIC_OBJ(id).data.counter = 0;
	ListEntry_Free(&topic_manager.head, &TOPIC_OBJ(id));
	return MROS_E_OK;
}
mRosReturnType RosTopic::remove(RosTopicIdType id)
{
	if (id > topic_manager.max_topic) {
		return MROS_E_RANGE;
	}
	if (TOPIC_OBJ(id).data.counter == 0) {
		return MROS_E_OK;
	}
	TOPIC_OBJ(id).data.counter = 0;
	ListEntry_Free(&topic_manager.head, &TOPIC_OBJ(id));
	return MROS_E_OK;
}

mRosReturnType RosTopic::add_data(RosTopicIdType id, memory::mRosMemoryListEntryType &data)
{
	if (id > topic_manager.max_topic) {
		return MROS_E_RANGE;
	}
	if (TOPIC_OBJ(id).data.counter == 0) {
		return MROS_E_INVAL;
	}
	if (TOPIC_OBJ(id).data.queue_head.entry_num >= TOPIC_OBJ(id).data.queue_maxsize) {
		return MROS_E_LIMIT;
	}
	ListEntry_AddEntry(&TOPIC_OBJ(id).data.queue_head, &data);
	return MROS_E_OK;
}

mRosReturnType RosTopic::get_data(RosTopicIdType id, memory::mRosMemoryListEntryType **data)
{
	memory::mRosMemoryListEntryType *datap;
	if (id > topic_manager.max_topic) {
		return MROS_E_RANGE;
	}
	if (TOPIC_OBJ(id).data.counter == 0) {
		return MROS_E_INVAL;
	}
	if (TOPIC_OBJ(id).data.queue_head.entry_num <= 0) {
		return MROS_E_NOENT;
	}
	datap = ListEntry_First(TOPIC_OBJ(id).data.queue_head.entries);
	ListEntry_RemoveEntry(&TOPIC_OBJ(id).data.queue_head, datap);
	*data = datap;
	return MROS_E_OK;
}

RosTopic::RosTopic()
{
	//TODO
}

RosTopic::~RosTopic()
{
	//TODO
}
