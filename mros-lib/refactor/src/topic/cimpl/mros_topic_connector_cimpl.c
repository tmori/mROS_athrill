#include "mros_topic_connector_cimpl.h"
#include "mros_config.h"
#include <stdlib.h>
#include <string.h>

mRosReturnType mros_topic_connector_init(mRosTopicConnectorConfigType *config, mRosTopicConnectorManagerType *mgrp)
{
	mgrp->conn_entries = config->conn_entries;
	mgrp->topic_entries = config->topic_entries;
	mgrp->max_connector = config->max_connector;
	for (mros_uint32 i = 0; i < mgrp->max_connector; i++) {
		mRosTopicConnectorListEntryType *entry = &(mgrp->conn_entries[i]);
		MROS_TOPIC_CONNECTOR_ENTRY_INIT(entry);
		entry->data.connector_id = MROS_ID(i);
		List_InitEmpty(&entry->data.queue_head, mRosMemoryListEntryType);
	}

	for (mros_uint32 i = 0; i < MROS_TOPIC_MAX_NUM; i++) {
		mRosTopicConnectorListEntryRootType *topic_entry = &(mgrp->topic_entries[i]);
		topic_entry->data.topic_id = MROS_ID_NONE;
		List_Init(&topic_entry->data.head, mRosTopicConnectorListEntryType, 0, NULL);
	}

	List_Init(&mgrp->topic_head, mRosTopicConnectorListEntryRootType, MROS_TOPIC_MAX_NUM, mgrp->topic_entries);
	List_Init(&mgrp->conn_head, mRosTopicConnectorListEntryType, mgrp->max_connector, mgrp->conn_entries);
	return MROS_E_OK;
}

mRosContainerObjType mros_topic_connector_get_topic_first(mRosTopicConnectorManagerType *mgrp)
{
	mRosTopicConnectorListEntryRootType *p;

	if (mgrp->topic_head.entry_num == 0) {
		return MROS_COBJ_NULL;
	}
	ListEntry_GetFirst(&mgrp->topic_head, &p);
	return (mRosContainerObjType)p;
}
mRosContainerObjType mros_topic_connector_get_topic_next(mRosTopicConnectorManagerType *mgrp, mRosContainerObjType obj)
{
	mRosTopicConnectorListEntryRootType *first;
	mRosTopicConnectorListEntryRootType *entry = (mRosTopicConnectorListEntryRootType*)obj;
	ListEntry_GetFirst(&mgrp->topic_head, &first);
	if (first == NULL) {
		return MROS_COBJ_NULL;
	}
	if (entry->next == first) {
		return MROS_COBJ_NULL;
	}
	return (mRosContainerObjType)entry->next;
}

mRosContainerObjType mros_topic_connector_get_first(mRosTopicConnectorManagerType *mgrp, mRosContainerObjType topic_obj)
{
	mRosTopicConnectorListEntryRootType *topic_entry = (mRosTopicConnectorListEntryRootType*)topic_obj;
	mRosTopicConnectorListEntryType *p;

	if (topic_entry->data.head.entry_num == 0) {
		return MROS_COBJ_NULL;
	}
	ListEntry_GetFirst(&topic_entry->data.head, &p);

	return (mRosContainerObjType)p;
}

mRosContainerObjType mros_topic_connector_get_next(mRosTopicConnectorManagerType *mgrp, mRosContainerObjType topic_obj, mRosContainerObjType obj)
{
	mRosTopicConnectorListEntryRootType *topic_entry = (mRosTopicConnectorListEntryRootType*)topic_obj;
	mRosTopicConnectorListEntryType *entry = (mRosTopicConnectorListEntryType*)obj;
	mRosTopicConnectorListEntryType *first;

	ListEntry_GetFirst(&topic_entry->data.head, &first);
	if (first == NULL) {
		return MROS_COBJ_NULL;
	}
	if (entry->next == first) {
		return MROS_COBJ_NULL;
	}
	return (mRosContainerObjType)entry->next;
}

static mRosTopicConnectorListEntryRootType *mros_topic_connector_get_topic_head(mRosTopicConnectorManagerType *mgrp, mRosTopicIdType topic_id)
{
	mRosTopicConnectorListEntryRootType *topic_p;

	ListEntry_Foreach(&mgrp->topic_head, topic_p) {
		if (topic_p->data.topic_id == topic_id) {
			return topic_p;
		}
	}
	return NULL;
}

static mRosTopicConnectorListEntryRootType *mros_topic_connector_create_topic_head(mRosTopicConnectorManagerType *mgrp, mRosTopicIdType topic_id)
{
	mRosTopicConnectorListEntryRootType *topic_p;

	ListEntry_Alloc(&mgrp->topic_head, mRosTopicConnectorListEntryRootType, &topic_p);
	if (topic_p == NULL) {
		return NULL;
	}
	topic_p->data.topic_id = topic_id;
	List_InitEmpty(&topic_p->data.head, mRosTopicConnectorListEntryType);
	ListEntry_AddEntry(&mgrp->topic_head, topic_p);
	return topic_p;
}

static mRosTopicConnectorListEntryType *mros_topic_connector_get_node(mRosTopicConnectorListEntryRootType *topic_p, mRosNodeIdType node_id)
{
	mRosTopicConnectorListEntryType *entry;

	ListEntry_Foreach(&topic_p->data.head, entry) {
		if ((entry->data.value.node_id == node_id)) {
			return entry;
		}
	}
	return NULL;
}

mRosReturnType mros_topic_connector_add(mRosTopicConnectorManagerType *mgrp, mRosTopicConnectorType *connector, mRosSizeType queue_length, mRosMemoryManagerType *mempool)
{
	mRosReturnType ret;
	mRosTopicConnectorListEntryRootType *topic_p;
	mRosTopicConnectorListEntryRootType *org_topic_p;
	mRosTopicConnectorListEntryType *entry;

	/* TODO LOCK */
	org_topic_p = mros_topic_connector_get_topic_head(mgrp, connector->topic_id);
	if (org_topic_p == NULL) {
		topic_p = mros_topic_connector_create_topic_head(mgrp, connector->topic_id);
	}
	else {
		topic_p = org_topic_p;
	}
	if (topic_p == NULL) {
		ret = MROS_E_NOMEM;
		goto errdone;
	}

	entry = mros_topic_connector_get_node(topic_p, connector->node_id);
	if (entry == NULL) {
		ListEntry_Alloc(&mgrp->conn_head, mRosTopicConnectorListEntryType, &entry);
		if (entry != NULL) {
			entry->data.value.topic_id = connector->topic_id;
			entry->data.value.node_id = connector->node_id;
			entry->data.value.func_id = connector->func_id;
			entry->data.queue_maxsize = queue_length;
			entry->data.mempool = mempool;
			List_InitEmpty(&entry->data.queue_head, mRosMemoryListEntryType);
			ListEntry_AddEntry(&topic_p->data.head, entry);
		}
		else {
			ret = MROS_E_NOMEM;
			goto errdone;
		}
	}
	return MROS_E_OK;

errdone:
	(void)mros_topic_connector_remove(mgrp, connector);

	return ret;}

mRosReturnType mros_topic_connector_remove(mRosTopicConnectorManagerType *mgrp, mRosTopicConnectorType *connector)
{
	mRosTopicConnectorListEntryRootType *topic_entryp;
	mRosTopicConnectorListEntryType *entryp;

	topic_entryp = mros_topic_connector_get_topic_head(mgrp, connector->topic_id);
	if (topic_entryp == NULL) {
		return MROS_E_NOENT;
	}
	entryp = mros_topic_connector_get_node(topic_entryp, connector->node_id);
	if (entryp == NULL) {
		return MROS_E_NOENT;
	}
	ListEntry_RemoveEntry(&topic_entryp->data.head, entryp);
	if (topic_entryp->data.head.entry_num == 0) {
		ListEntry_RemoveEntry(&mgrp->topic_head, topic_entryp);
	}
	return MROS_E_OK;
}

mRosReturnType mros_topic_connector_get(mRosContainerObjType obj, mRosTopicConnectorType *connector)
{
	mRosTopicConnectorListEntryType *entry = (mRosTopicConnectorListEntryType*)obj;
	*connector = entry->data.value;
	return MROS_E_OK;
}

mRosContainerObjType mros_topic_connector_get_obj(mRosTopicConnectorManagerType *mgrp, mRosTopicConnectorType *connector)
{
	mRosTopicConnectorListEntryRootType *tp;
	mRosTopicConnectorListEntryRootType *topic_p = NULL;
	mRosTopicConnectorListEntryType *p;
	mRosTopicConnectorListEntryType *entry = NULL;

	ListEntry_Foreach(&mgrp->topic_head, tp) {
		if (tp->data.topic_id == connector->topic_id) {
			topic_p = tp;
			break;
		}
	}
	if (tp == NULL) {
		return MROS_COBJ_NULL;
	}

	ListEntry_Foreach(&topic_p->data.head, p) {
		if ((p->data.value.node_id == connector->node_id)) {
			entry = p;
			break;
		}
	}
	if (entry == NULL) {
		return MROS_COBJ_NULL;
	}
	return (mRosContainerObjType)entry;
}

mRosReturnType mros_topic_connector_get_topic(mRosContainerObjType topic_obj, mRosTopicIdType *topic_id)
{
	mRosTopicConnectorListEntryRootType *topic_p = (mRosTopicConnectorListEntryRootType*)topic_obj;
	*topic_id = topic_p->data.topic_id;
	return MROS_E_OK;
}


mRosReturnType mros_topic_connector_add_data(mRosContainerObjType obj, const char* data, mRosSizeType len)
{
	mRosReturnType ret;
	mRosMemoryListEntryType *mem_entryp;
	mRosTopicConnectorListEntryType *entry = (mRosTopicConnectorListEntryType*)obj;
	if (entry->data.queue_head.entry_num >= entry->data.queue_maxsize) {
		return MROS_E_LIMIT;
	}

	if (entry->data.mempool == NULL) {
		//TODO 要検討
		//購読の場合は，キューにつなげるのではなく，
		//INNER：コールバック関数呼び出し
		//OUTER:TCP送信
		//の方がよいと思われる
		return MROS_E_INVAL;
	}

	ret = mros_mem_alloc(entry->data.mempool, len, &mem_entryp);
	if (ret != MROS_E_OK) {
		return ret;
	}

	mem_entryp->data.size = len;
	memcpy(mem_entryp->data.memp, data, mem_entryp->data.size);
	ListEntry_AddEntry(&entry->data.queue_head, mem_entryp);

	return MROS_E_OK;
}

mRosMemoryListEntryType *mros_topic_connector_get_data(mRosContainerObjType obj)
{
	mRosMemoryListEntryType *data;
	mRosTopicConnectorListEntryType *entry = (mRosTopicConnectorListEntryType*)obj;

	if (entry->data.queue_head.entry_num == 0) {
		return NULL;
	}
	//TODO 要検討
	//出版の場合は，キューから取り出すのではなく，
	//OUTER:TCP受信
	//になるとと思われる
	ListEntry_GetFirst(&entry->data.queue_head, &data);
	ListEntry_RemoveEntry(&entry->data.queue_head, data);
	return data;
}

