#include "mros_topic_cimpl.h"
#include <stdlib.h>
#include <string.h>

static RosTopicManagerType 	topic_manager;
#define TOPIC_OBJ(id)		topic_manager.topic_entries[TOPIC_INDEX((id))]

static mRosTopicListEntryType topic_entries[MROS_TOPIC_MAX_NUM];

mRosReturnType mros_topic_init(void)
{
	topic_manager.topic_entries = topic_entries;
	topic_manager.max_topic = MROS_TOPIC_MAX_NUM;
	for (mros_uint32 i = 0; i < topic_manager.max_topic; i++) {
		mRosTopicListEntryType *entry = &(topic_manager.topic_entries[i]);
		MROS_TOPIC_ENTRY_INIT(entry);
		entry->data.topic_id = TOPIC_ID(i);
		List_Init(&(entry->data.queue_head), mRosMemoryListEntryType, 0, NULL);
	}
	List_Init(&topic_manager.head, mRosTopicListEntryType, topic_manager.max_topic, topic_manager.topic_entries);

	return MROS_E_OK;
}

mRosContainerObjType mros_topic_get_first(void)
{
	mRosTopicListEntryType *p;

	if (topic_manager.head.entry_num == 0) {
		return MROS_COBJ_NULL;
	}
	ListEntry_GetFirst(&topic_manager.head, &p);
	return (mRosContainerObjType)p;
}

mRosContainerObjType mros_topic_get_next(mRosContainerObjType obj)
{
	mRosTopicListEntryType *first;
	mRosTopicListEntryType *entry = (mRosTopicListEntryType*)obj;
	ListEntry_GetFirst(&topic_manager.head, &first);
	if (first == NULL) {
		return MROS_COBJ_NULL;
	}
	if (entry->next == first) {
		return MROS_COBJ_NULL;
	}
	return (mRosContainerObjType)entry->next;
}

mRosTopicIdType mros_topic_get_id(mRosContainerObjType obj)
{
	mRosTopicListEntryType *entry = (mRosTopicListEntryType*)obj;
	return entry->data.topic_id;
}

mRosReturnType mros_topic_get(const char *topic_name, mRosTopicIdType *id)
{
	mRosTopicListEntryType *p;
	mros_uint32 len = strlen(topic_name);

	*id = MROS_ID_NONE;
	ListEntry_Foreach(&topic_manager.head, p) {
		if (len != p->data.namelen) {
			continue;
		}
		if (!strcmp(p->data.topic_name, topic_name)) {
			*id = p->data.topic_id;
			break;
		}
	}
	if (*id == MROS_ID_NONE) {
		return MROS_E_NOENT;
	}
	return MROS_E_OK;
}

mRosReturnType mros_topic_create(const char *topic_name, mRosTopicIdType *id)
{
	mRosTopicListEntryType *p;
	mros_uint32 len = strlen(topic_name);

	mRosReturnType ret = mros_topic_get(topic_name, id);
	if (ret == MROS_E_OK) {
		return MROS_E_EXIST;
	}

	ListEntry_Alloc(&topic_manager.head, mRosTopicListEntryType, &p);
	if (p == NULL) {
		return MROS_E_NOMEM;
	}
	*id = p->data.topic_id;
	p->data.namelen = len;
	p->data.topic_name = topic_name;
	ListEntry_AddEntry(&topic_manager.head, p);
	return MROS_E_OK;
}

mRosReturnType mros_topic_set_quesize_byname(const char *topic_name, mRosSizeType size)
{
	mRosTopicIdType id;

	mRosReturnType ret = mros_topic_get(topic_name, &id);
	if (ret != MROS_E_OK) {
		return ret;
	}
	TOPIC_OBJ(id).data.queue_maxsize = size;
	return MROS_E_OK;
}
mRosReturnType mros_topic_set_quesize_byid(mRosTopicIdType id, mRosSizeType size)
{
	if (id > topic_manager.max_topic) {
		return MROS_E_RANGE;
	}
	TOPIC_OBJ(id).data.queue_maxsize = size;
	return MROS_E_OK;
}

const char *mros_topic_get_topic_name(mRosTopicIdType id)
{
	if (id > topic_manager.max_topic) {
		return NULL;
	}
	return TOPIC_OBJ(id).data.topic_name;
}


mRosReturnType mros_topic_remove_byname(const char *topic_name)
{
	mRosTopicIdType id;

	mRosReturnType ret = mros_topic_get(topic_name, &id);
	if (ret != MROS_E_OK) {
		return ret;
	}
	ListEntry_Free(&topic_manager.head, &TOPIC_OBJ(id));
	return MROS_E_OK;
}
mRosReturnType mros_topic_remove_byid(mRosTopicIdType id)
{
	if (id > topic_manager.max_topic) {
		return MROS_E_RANGE;
	}
	ListEntry_Free(&topic_manager.head, &TOPIC_OBJ(id));
	return MROS_E_OK;
}

mRosReturnType mros_topic_add_data(mRosTopicIdType id, mRosMemoryListEntryType *data)
{
	if (id > topic_manager.max_topic) {
		return MROS_E_RANGE;
	}
	if (TOPIC_OBJ(id).data.queue_head.entry_num >= TOPIC_OBJ(id).data.queue_maxsize) {
		return MROS_E_LIMIT;
	}
	ListEntry_AddEntry(&TOPIC_OBJ(id).data.queue_head, data);
	return MROS_E_OK;
}

mRosReturnType mros_topic_get_data(mRosTopicIdType id, mRosMemoryListEntryType **data)
{
	mRosMemoryListEntryType *datap;
	if (id > topic_manager.max_topic) {
		return MROS_E_RANGE;
	}
	if (TOPIC_OBJ(id).data.queue_head.entry_num <= 0) {
		return MROS_E_NOENT;
	}
	datap = ListEntry_First(TOPIC_OBJ(id).data.queue_head.entries);
	ListEntry_RemoveEntry(&TOPIC_OBJ(id).data.queue_head, datap);
	*data = datap;
	return MROS_E_OK;
}
