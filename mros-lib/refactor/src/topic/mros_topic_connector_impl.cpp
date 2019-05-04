#include "mros_topic_connector.h"
#include "mros_list.h"
#include <stdlib.h>

using namespace mros::topic;

typedef struct {
	mros_uint32					counter;
	RosTopicConnectorIdType		connector_id;
	RosTopicIdType				topic_id;
	RosNodeIdType				src_id;
	RosNodeIdType				dst_id;
} RosConnectorEntryType;

typedef ListEntryType(RosConnectorEntryListType, RosConnectorEntryType) RosConnectorEntryListType;
typedef ListHeadType(RosConnectorEntryListType) RosConnectorEntryListHeadType;

#define ROS_CONNECTOR_ENTRY_INIT(entryp)	\
do {	\
	(entryp)->data.counter = 0;		\
	(entryp)->data.src_id = MROS_ID_NONE;		\
	(entryp)->data.dst_id = MROS_ID_NONE;		\
	(entryp)->data.topic_id = MROS_ID_NONE;	\
} while (0)

typedef struct {
	RosConnectorEntryListHeadType head;
	RosConnectorEntryListType *connector_entries;
} RosConnectorManagerType;

#define CONNECTOR_ID(index)		((index) + 1U)
#define CONNECTOR_INDEX(id)		((id) - 1U)


RosConnectorManagerType conn_manager;

#define CONNECTOR_OBJ(id)		conn_manager.connector_entries[CONNECTOR_INDEX((id))]

mRosReturnType topology::RosTopicConnector::init(mRosSizeType max_connector)
{
	conn_manager.connector_entries = (RosConnectorEntryListType *)malloc(max_connector * sizeof(RosConnectorEntryListType));
	//TODO ASSERT
	for (int i = 0; i < max_connector; i++) {
		RosConnectorEntryListType *entry = &(conn_manager.connector_entries[i]);
		entry->data.connector_id = CONNECTOR_ID(i);
		ROS_CONNECTOR_ENTRY_INIT(entry);
	}
	List_Init(&conn_manager.head, RosConnectorEntryListType, max_connector, conn_manager.connector_entries);

	return MROS_E_OK;
}

mRosReturnType topology::RosTopicConnector::get_topics(PrimitiveContainer<RosTopicConnectorIdType> &container)
{
	RosConnectorEntryListType *p;
	container.usecount = 0;
	int i = 0;

	ListEntry_Foreach(&conn_manager.head, p) {
		if (container.usecount >= container.array_size) {
			break;
		}
		if ((p->data.src_id != MROS_ID_NONE) && (p->data.dst_id != MROS_ID_NONE)) {
			container[i] = p->data.connector_id;
			container.usecount++;
			p->data.counter++;
			i++;
		}
	}

	return MROS_E_OK;
}

mRosReturnType topology::RosTopicConnector::put_topics(PrimitiveContainer<RosTopicConnectorIdType> &container)
{
	for (int i = 0; i < container.usecount; i++) {
		CONNECTOR_OBJ(container[i]).data.counter--;
	}
	container.usecount = 0;
	return MROS_E_OK;
}

static mRosReturnType topology::RosTopicConnector::add_pubnode_topic(const char* topic_name, RosNodeIdType src)
{
	RosTopicIdType topic_id;
	mRosReturnType ret;
	RosConnectorEntryListType *entry = NULL;
	RosConnectorEntryListType *p;
	bool isTopicFound = false;

	ret = RosTopic::create(topic_name, topic_id);
	if (ret != MROS_E_OK) {
		goto errdone;
	}

	/*
	 * 1) entry: topicなし, src:-, dst:-　   　　：次のステップで Alloc
	 * 2) entry: topicあり, src:なし, dst:NONE：srcを設定する
	 * 3) entry: topicあり, src:なし, dst:あり　：srcを設定するT
	 * 4) entry: topicあり, src:同じ, dst:NONE：何もしない
	 * 5) entry: topicあり, src:同じ, dst:あり　：何もしない
	 * 6) entry: topicあり, src:違う, dst:NONE：EEXIST
	 * 7) entry: topicあり, src:違う, dst:あり　：EEXIST
	 */
	ListEntry_Foreach(&conn_manager.head, p) {
		if (p->data.topic_id == topic_id) {
			isTopicFound = true;
			if ((p->data.src_id != MROS_ID_NONE) && (p->data.src_id != src)) {
				ret = MROS_E_EXIST;
				goto errdone;
			}
		}
	}
	if (isTopicFound) {
		ListEntry_Foreach(&conn_manager.head, p) {
			if (p->data.topic_id == topic_id) {
				p->data.src_id = src;
			}
		}
	}
	else {
		ListEntry_Alloc(&conn_manager.head, RosConnectorEntryListType, &entry);
		if (entry == NULL) {
			ret = MROS_E_NOMEM;
			goto errdone;
		}
		entry->data.counter = 1U;
		entry->data.topic_id = topic_id;
		entry->data.src_id = src;
		ListEntry_AddEntry(&conn_manager.head, entry);
	}

	return MROS_E_OK;

errdone:
	if (entry != NULL) {
		ListEntry_Free(&conn_manager.head, entry);
	}
	return ret;
}

static mRosReturnType topology::RosTopicConnector::add_subnode_topic(const char* topic_name, RosNodeIdType dst)
{
	RosTopicIdType topic_id;
	mRosReturnType ret;
	RosConnectorEntryListType *entry = NULL;
	RosConnectorEntryListType *p;
	RosNodeIdType src_id = MROS_ID_NONE;

	/* TODO LOCK */
	ret = RosTopic::create(topic_name, topic_id);
	if (ret != MROS_E_OK) {
		goto errdone;
	}

	/*
	 * 1) entry: topicなし, src:-, dst:-　   　　：次のステップで Alloc
	 * 2) entry: topicあり, src:なし, dst:NONE：本エントリを使用する
	 * 3) entry: topicあり, src:なし, dst:同じ　：EEXIST
	 * 4) entry: topicあり, src:あり, dst:NONE：本エントリを使用する
	 * 5) entry: topicあり, src:あり, dst:同じ　：EEXIST
	 */
	ListEntry_Foreach(&conn_manager.head, p) {
		if (p->data.topic_id == topic_id) {
			src_id = p->data.src_id;
			if (p->data.dst_id == dst) {
				ret = MROS_E_EXIST;
				goto errdone;
			}
			else if (p->data.dst_id == MROS_ID_NONE) {
				entry = p;
				break;
			}
		}
	}
	if (entry == NULL) {
		ListEntry_Alloc(&conn_manager.head, RosConnectorEntryListType, &entry);
		if (entry == NULL) {
			ret = MROS_E_NOMEM;
			goto errdone;
		}
		entry->data.counter = 1U;
		ListEntry_AddEntry(&conn_manager.head, entry);
	}
	entry->data.topic_id = topic_id;
	entry->data.src_id = src_id;
	entry->data.dst_id = dst;
	/* TODO UNLOCK */
	return MROS_E_OK;

errdone:
	if (entry != NULL) {
		ListEntry_Free(&conn_manager.head, entry);
	}
	/* TODO UNLOCK */
	return ret;
}


topology::RosTopicConnector::RosTopicConnector()
{
	//TODO
}

topology::RosTopicConnector::~RosTopicConnector()
{
	//TODO
}
