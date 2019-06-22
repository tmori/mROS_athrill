#ifndef _MROS_TOPIC_NODE_CIMPL_H_
#define _MROS_TOPIC_NODE_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_list.h"
#include "mros_memory.h"

typedef struct {
	mRosNodeIdType 				topic_node_id;
	mRosNodeIdType 				node_id;
	mRosFuncIdType 				func_id;
	mRosSizeType				queue_maxsize;
	mRosMemoryListHeadType 		queue_head;
} mRosTopicNodeEntryType;

#define MROS_TOPIC_NODE_ENTRY_INIT(entryp)	\
do {	\
	(entryp)->data.topic_node_id = MROS_ID_NONE;	\
	(entryp)->data.node_id = MROS_ID_NONE;	\
	(entryp)->data.func_id = MROS_ID_NONE;	\
	(entryp)->data.queue_maxsize = 1; \
} while (0)

typedef ListEntryType(mRosTopicNodeListEntryType, mRosTopicNodeEntryType) mRosTopicNodeListEntryType;
typedef ListHeadType(mRosTopicNodeListEntryType) mRosTopicNodeEntryHeadType;

typedef struct {
	mRosTopicNodeEntryHeadType	 	head;
	mRosTopicNodeListEntryType 		*topic_node_entries;
	mRosSizeType					max_topic_node;
} mRosTopicNodeManagerType;

/*
 * config topic node
 */
typedef struct {
	mRosSizeType 				max_topic_node;
	mRosTopicNodeListEntryType *topic_node_entries;
} mRosTopicNodeConfigType;

extern mRosReturnType mros_topic_node_init(mRosTopicNodeConfigType * config, mRosTopicNodeManagerType *tnode_mgrp);
extern mRosReturnType mros_topic_node_create(mRosTopicNodeManagerType *tnode_mgrp, mRosNodeIdType snode_id, mRosNodeIdType *tnode_id);
extern mRosReturnType mros_topic_set_quesize(mRosTopicNodeManagerType *tnode_mgrp, mRosNodeIdType tnode_id, mRosSizeType size);
extern mRosReturnType mros_topic_remove(mRosTopicNodeManagerType *tnode_mgrp, mRosNodeIdType tnode_id);
extern mRosReturnType mros_topic_add_data(mRosTopicNodeManagerType *tnode_mgrp, mRosNodeIdType tnode_id, mRosMemoryListEntryType *data);
extern mRosReturnType mros_topic_get_data(mRosTopicNodeManagerType *tnode_mgrp, mRosNodeIdType tnode_id, mRosMemoryListEntryType **data);

/*
 * Topic Node Config APIs
 */
#define MROS_TOPIC_NODE_CONFIG_DECLARE_MANAGER(tnode_instance_name, max_topic_node)	\
	static mRosTopicNodeListEntryType tnode_instance_name##_array [(topic_node_num)];	\
	static mRosTopicNodeManagerType tnode_instance_name##_mgr;	\
	static mRosTopicNodeConfigType  tnode_instance_name##_config = {	\
		(max_topic_node),	\
		tnode_config_name##_array,	\
	};


#ifdef __cplusplus
}
#endif
#endif /* _MROS_TOPIC_NODE_CIMPL_H_ */
