#include "mros_topic_connector.h"
#include "mros_node.h"
#include "mros_list.h"
#include <stdlib.h>

using namespace mros::topic;
using namespace mros::node;


typedef struct {
	mros_uint32							counter;
	mRosTopicConnectorIdType				connector_id;
	topology::RosTopicConnectorType		value;
} RosConnectorEntryType;

typedef ListEntryType(RosConnectorListEntryType, RosConnectorEntryType) RosConnectorListEntryType;
typedef ListHeadType(RosConnectorListEntryType) RosConnectorListHeadType;

typedef struct {
	mRosTopicIdType						topic_id;
	RosConnectorListHeadType			head;
} RosConnectorTopicEntryType;

typedef ListEntryType(RosConnectorTopicListEntryType, RosConnectorTopicEntryType) RosConnectorTopicListEntryType;
typedef ListHeadType(RosConnectorTopicListEntryType) RosConnectorTopicListHeadType;


#define ROS_CONNECTOR_ENTRY_INIT(entryp)	\
do {	\
	(entryp)->data.counter = 0;		\
	(entryp)->data.value.topic_id = MROS_ID_NONE;		\
	(entryp)->data.value.node_id = MROS_ID_NONE;		\
	(entryp)->data.value.func_id = MROS_ID_NONE;	\
} while (0)

typedef struct {
	mRosSizeType						max_connector;
	RosConnectorListHeadType 			conn_head;
	RosConnectorListEntryType 			*conn_entries;

	RosConnectorTopicListHeadType 		topic_head;
	RosConnectorTopicListEntryType		*topic_entries;
} RosConnectorManagerType;

typedef struct {
	RosConnectorManagerType		pub;
	RosConnectorManagerType		sub;
} RosTopicConnectorManagerType;

#define CONNECTOR_ID(index)		((index) + 1U)
#define CONNECTOR_INDEX(id)		((id) - 1U)

static RosTopicConnectorManagerType conn_manager;

#define CONNECTOR_OBJ(mgrp, id)		(mgrp)->conn_entries[CONNECTOR_INDEX((id))]

static mRosReturnType mRosTopicConnector_init(mRosSizeType max_connector, RosConnectorManagerType *mgrp)
{
	mgrp->conn_entries = (RosConnectorListEntryType *)malloc(max_connector * sizeof(RosConnectorListEntryType));
	if (mgrp->conn_entries != NULL) {
		return MROS_E_NOMEM;
	}
	mgrp->topic_entries = (RosConnectorTopicListEntryType *)malloc(max_connector * sizeof(RosConnectorTopicListEntryType));
	if (mgrp->topic_entries != NULL) {
		free(mgrp->conn_entries);
		mgrp->conn_entries = NULL;
		return MROS_E_NOMEM;
	}
	for (mros_uint32 i = 0; i < max_connector; i++) {
		RosConnectorListEntryType *entry = &(mgrp->conn_entries[i]);
		ROS_CONNECTOR_ENTRY_INIT(entry);
		entry->data.connector_id = CONNECTOR_ID(i);

		RosConnectorTopicListEntryType *topic_entry = &(mgrp->topic_entries[i]);
		topic_entry->data.topic_id = MROS_ID_NONE;
		List_InitEmpty(&topic_entry->data.head, RosConnectorListEntryType);
	}

	mgrp->max_connector = max_connector;
	List_Init(&mgrp->topic_head, RosConnectorTopicListEntryType, max_connector, mgrp->topic_entries);
	List_Init(&mgrp->conn_head, RosConnectorListEntryType, max_connector, mgrp->conn_entries);
	return MROS_E_OK;
}
static RosConnectorTopicListEntryType *mRosTopicConnector_get_topic_head(RosConnectorManagerType *mgrp, mRosTopicIdType topic_id)
{
	RosConnectorTopicListEntryType *topic_p;

	ListEntry_Foreach(&mgrp->topic_head, topic_p) {
		if (topic_p->data.topic_id == topic_id) {
			return topic_p;
		}
	}
	return NULL;
}
static RosConnectorTopicListEntryType *mRosTopicConnector_create_topic_head(RosConnectorManagerType *mgrp, mRosTopicIdType topic_id)
{
	RosConnectorTopicListEntryType *topic_p;

	ListEntry_Alloc(&mgrp->topic_head, RosConnectorTopicListEntryType, &topic_p);
	if (topic_p == NULL) {
		return NULL;
	}
	topic_p->data.topic_id = topic_id;
	List_InitEmpty(&topic_p->data.head, RosConnectorListEntryType);
	ListEntry_AddEntry(&mgrp->topic_head, topic_p);
	return NULL;
}

static mRosReturnType mRosTopicConnector_get_connectors(mRosTopicIdType topic_id, RosConnectorManagerType *mgrp, PrimitiveContainer<mRosTopicConnectorIdType> &container)
{
	RosConnectorTopicListEntryType *topic_p;
	RosConnectorListEntryType *p;
	container.usecount = 0;
	mros_uint32 i = 0;

	topic_p = mRosTopicConnector_get_topic_head(mgrp, topic_id);
	if (topic_p == NULL) {
		return MROS_E_NOENT;
	}

	ListEntry_Foreach(&topic_p->data.head, p) {
		if (container.usecount >= container.size()) {
			break;
		}
		RosNodeType type;
		mRosReturnType ret = RosNode::type(p->data.value.node_id,  type);
		if ((ret == MROS_E_OK) && (type == ROS_NODE_TYPE_INNER)) {
			container[i] = p->data.connector_id;
			container.usecount++;
			p->data.counter++;
			i++;
		}
	}

	return MROS_E_OK;
}

static mRosReturnType mRosTopicConnector_get_topics(RosConnectorManagerType *mgrp, PrimitiveContainer<mRosTopicIdType> &container)
{
	RosConnectorTopicListEntryType *topic_p;
	container.usecount = 0;
	mros_uint32 i = 0;

	ListEntry_Foreach(&mgrp->topic_head, topic_p) {
		if (container.usecount >= container.size()) {
			break;
		}
		container[i] = topic_p->data.topic_id;
		container.usecount++;
		i++;
	}
	return MROS_E_OK;
}

static mRosReturnType mRosTopicConnector_rel_connectors(RosConnectorManagerType *mgrp, PrimitiveContainer<mRosTopicConnectorIdType> &container)
{
	for (mros_uint32 i = 0; i < container.usecount; i++) {
		CONNECTOR_OBJ(mgrp, container[i]).data.counter--;
	}
	container.usecount = 0;
	return MROS_E_OK;
}

static mRosReturnType mRosTopicConnector_get(RosConnectorManagerType *mgrp, mRosTopicConnectorIdType id, topology::RosTopicConnectorType &connector)
{
	if (id > mgrp->max_connector) {
		return MROS_E_RANGE;
	}
	connector = CONNECTOR_OBJ(mgrp, id).data.value;
	return MROS_E_OK;
}

static RosConnectorListEntryType *mRosTopicConnector_get_node(RosConnectorTopicListEntryType *topic_p, mRosNodeIdType node_id)
{
	RosConnectorListEntryType *entry;

	ListEntry_Foreach(&topic_p->data.head, entry) {
		if ((entry->data.value.node_id == node_id)) {
			return entry;
		}
	}
	return NULL;
}


static mRosReturnType mRosTopicConnector_add(RosConnectorManagerType *mgrp, const char* topic_name, mRosNodeIdType node_id, mRosFuncIdType func_id)
{
	mRosTopicIdType topic_id;
	mRosReturnType ret;
	RosConnectorTopicListEntryType *topic_p;
	RosConnectorListEntryType *entry;
	bool isTopicCreated = false;

	/* TODO LOCK */
	ret = RosTopic::create(topic_name, topic_id);
	if (ret == MROS_E_OK) {
		isTopicCreated = true;
	}
	else if (ret != MROS_E_EXIST) {
		goto errdone;
	}

	topic_p = mRosTopicConnector_get_topic_head(mgrp, topic_id);
	if (topic_p == NULL) {
		topic_p = mRosTopicConnector_create_topic_head(mgrp, topic_id);
		if (topic_p == NULL) {
			ret = MROS_E_NOMEM;
			goto errdone;
		}
	}

	entry = mRosTopicConnector_get_node(topic_p, node_id);
	if (entry == NULL) {
		ListEntry_Alloc(&mgrp->conn_head, RosConnectorListEntryType, &entry);
		if (entry != NULL) {
			entry->data.counter = 1U;
			entry->data.value.topic_id = topic_id;
			entry->data.value.node_id = node_id;
			entry->data.value.func_id = func_id;
			ListEntry_AddEntry(&topic_p->data.head, entry);
		}
		else {
			ret = MROS_E_NOMEM;
			goto errdone;
		}
	}

	return MROS_E_OK;

errdone:
	if (isTopicCreated) {
		(void)RosTopic::remove(topic_name);
	}

	return ret;
}

mRosReturnType topology::RosTopicConnector::init(mRosSizeType max_pub_connector, mRosSizeType max_sub_connector)
{
	/*
	 * publish
	 */
	(void)mRosTopicConnector_init(max_pub_connector, &conn_manager.pub);
	//TODO ASSERT;
	/*
	 * subscribe
	 */
	(void)mRosTopicConnector_init(max_sub_connector, &conn_manager.sub);
	//TODO ASSERT;
	return MROS_E_OK;
}


mRosReturnType topology::RosTopicConnector::get_pub_connectors(mRosTopicIdType topic_id, PrimitiveContainer<mRosTopicConnectorIdType> &container)
{
	return mRosTopicConnector_get_connectors(topic_id, &conn_manager.pub, container);
}

mRosReturnType topology::RosTopicConnector::get_sub_connectors(mRosTopicIdType topic_id, PrimitiveContainer<mRosTopicConnectorIdType> &container)
{
	return mRosTopicConnector_get_connectors(topic_id, &conn_manager.sub, container);
}


mRosReturnType topology::RosTopicConnector::rel_pub_connectors(PrimitiveContainer<mRosTopicConnectorIdType> &container)
{
	return mRosTopicConnector_rel_connectors(&conn_manager.pub, container);
}

mRosReturnType topology::RosTopicConnector::rel_sub_connectors(PrimitiveContainer<mRosTopicConnectorIdType> &container)
{
	return mRosTopicConnector_rel_connectors(&conn_manager.sub, container);
}

mRosReturnType topology::RosTopicConnector::get_pub(mRosTopicConnectorIdType id, RosTopicConnectorType &connector)
{
	return mRosTopicConnector_get(&conn_manager.pub, id, connector);
}

mRosReturnType topology::RosTopicConnector::get_sub(mRosTopicConnectorIdType id, RosTopicConnectorType &connector)
{
	return mRosTopicConnector_get(&conn_manager.sub, id, connector);
}

mRosReturnType topology::RosTopicConnector::add_pub(const char* topic_name, mRosNodeIdType src)
{
	return mRosTopicConnector_add(&conn_manager.pub, topic_name, src, MROS_ID_NONE);
}

mRosReturnType topology::RosTopicConnector::add_sub(const char* topic_name, mRosNodeIdType dst, mRosFuncIdType func)
{
	return mRosTopicConnector_add(&conn_manager.sub, topic_name, dst, func);
}
mRosReturnType topology::RosTopicConnector::get_pub_topics(PrimitiveContainer<mRosTopicIdType> &container)
{
	return mRosTopicConnector_get_topics(&conn_manager.pub, container);
}
mRosReturnType topology::RosTopicConnector::get_sub_topics(PrimitiveContainer<mRosTopicIdType> &container)
{
	return mRosTopicConnector_get_topics(&conn_manager.sub, container);
}

topology::RosTopicConnector::RosTopicConnector()
{
	//TODO
}

topology::RosTopicConnector::~RosTopicConnector()
{
	//TODO
}
