#include "mros_topic_node_cimpl.h"
#include <stdlib.h>

mRosReturnType mros_topic_node_init(mRosTopicNodeConfigType * config, mRosTopicNodeManagerType *tnode_mgrp)
{
	tnode_mgrp->max_topic_node = config->max_topic_node;
	tnode_mgrp->topic_node_entries = config->topic_node_entries;
	for (mros_uint32 i = 0; i < tnode_mgrp->max_topic_node; i++) {
		mRosTopicNodeListEntryType *entry = &(tnode_mgrp->topic_node_entries[i]);
		MROS_TOPIC_NODE_ENTRY_INIT(entry);
		entry->data.topic_node_id = MROS_ID(i);
		List_Init(&(entry->data.queue_head), mRosMemoryListEntryType, 0, NULL);
	}
	List_Init(&tnode_mgrp->head, mRosTopicNodeListEntryType, tnode_mgrp->max_topic_node, tnode_mgrp->topic_node_entries);

	return MROS_E_OK;
}

mRosReturnType mros_topic_node_create(mRosTopicNodeManagerType *tnode_mgrp, mRosNodeIdType snode_id, mRosNodeIdType *tnode_id)
{
	mRosTopicNodeListEntryType *p;

	mRosReturnType ret = mros_topic_node_get(tnode_mgrp, snode_id);
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
mRosReturnType mros_topic_set_quesize(mRosTopicNodeManagerType *tnode_mgrp, mRosNodeIdType tnode_id, mRosSizeType size)
{
	return MROS_E_OK;
}
mRosReturnType mros_topic_remove(mRosTopicNodeManagerType *tnode_mgrp, mRosNodeIdType tnode_id)
{
	return MROS_E_OK;
}
mRosReturnType mros_topic_add_data(mRosTopicNodeManagerType *tnode_mgrp, mRosNodeIdType tnode_id, mRosMemoryListEntryType *data)
{
	return MROS_E_OK;
}
mRosReturnType mros_topic_get_data(mRosTopicNodeManagerType *tnode_mgrp, mRosNodeIdType tnode_id, mRosMemoryListEntryType **data)
{
	return MROS_E_OK;
}
