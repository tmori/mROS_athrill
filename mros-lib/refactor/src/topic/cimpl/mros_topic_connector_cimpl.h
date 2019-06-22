#ifndef _MROS_TOPIC_CONNECTOR_CIMPL_H_
#define _MROS_TOPIC_CONNECTOR_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_types.h"
#include "mros_memory.h"

typedef struct {
	mRosTopicIdType				topic_id;
	mRosNodeIdType				node_id;
	mRosFuncIdType				func_id;
} mRosTopicConnectorType;

typedef struct {
	mRosTopicConnectorIdType	connector_id;
	mRosTopicConnectorType		value;
	mRosSizeType				queue_maxsize;
	mRosMemoryListHeadType 		queue_head;
} mRosTopicConnectorEntryType;
typedef ListEntryType(mRosTopicConnectorListEntryType, mRosTopicConnectorEntryType) mRosTopicConnectorListEntryType;
typedef ListHeadType(mRosTopicConnectorListEntryType) mRosTopicConnectorListHeadType;

#define MROS_TOPIC_CONNECTOR_ENTRY_INIT(entryp)	\
do {	\
	(entryp)->data.queue_maxsize = 1U;		\
	(entryp)->data.value.topic_id = MROS_ID_NONE;		\
	(entryp)->data.value.node_id = MROS_ID_NONE;		\
	(entryp)->data.value.func_id = MROS_ID_NONE;	\
} while (0)


typedef struct {
	mRosTopicIdType						topic_id;
	mRosTopicConnectorListHeadType		head;
} mRosTopicConnectorEntryRootType;
typedef ListEntryType(mRosTopicConnectorListEntryRootType, mRosTopicConnectorEntryRootType) mRosTopicConnectorListEntryRootType;
typedef ListHeadType(mRosTopicConnectorListEntryRootType) mRosTopicConnectorListEntryRootHeadType;

typedef struct {
	mRosSizeType								max_connector;

	mRosTopicConnectorListHeadType			 	conn_head;
	mRosTopicConnectorListEntryType				*conn_entries;

	mRosTopicConnectorListEntryRootHeadType		topic_head;
	mRosTopicConnectorListEntryRootType			*topic_entries;
} mRosTopicConnectorManagerType;

typedef struct {
	mRosSizeType								max_connector;
	mRosTopicConnectorListEntryType				*conn_entries;
	mRosTopicConnectorListEntryRootType			*topic_entries;
} mRosTopicConnectorConfigType;

extern mRosReturnType mros_topic_connector_init(mRosTopicConnectorConfigType *config, mRosTopicConnectorManagerType *mgrp);

extern mRosContainerObjType mros_topic_connector_get_topic_first(mRosTopicConnectorManagerType *mgrp);
extern mRosContainerObjType mros_topic_connector_get_topic_next(mRosTopicConnectorManagerType *mgrp, mRosContainerObjType obj);

extern mRosContainerObjType mros_topic_connector_get_first(mRosTopicConnectorManagerType *mgrp, mRosContainerObjType topic_obj);
extern mRosContainerObjType mros_topic_connector_get_next(mRosTopicConnectorManagerType *mgrp, mRosContainerObjType topic_obj, mRosContainerObjType obj);

extern mRosReturnType mros_topic_connector_add(mRosTopicConnectorManagerType *mgrp, mRosTopicConnectorType *connector);
extern mRosReturnType mros_topic_connector_remove(mRosTopicConnectorManagerType *mgrp, mRosTopicConnectorType *connector);


extern mRosReturnType mros_topic_connector_add_data(mRosContainerObjType obj, mRosMemoryListEntryType *data);
extern mRosMemoryListEntryType *mros_topic_connector_get_data(mRosContainerObjType obj);

/*
 * topic connector Config APIs
 */
#define MROS_TOPIC_CONNECTOR_CONFIG_DECLARE_MANAGER(manager_name, conn_entry_num)	\
	static mRosTopicConnectorListEntryType manager_name##_conn_array [(conn_entry_num)];	\
	static mRosTopicConnectorListEntryRootType manager_name##_topic_array [MROS_TOPIC_MAX_NUM];	\
	static mRosTopicConnectorManagerType manager_name;	\
	static mRosTopicConnectorConfigType manager_name##_config = {	\
		(conn_entry_num),	\
		manager_name##_conn_array,	\
		manager_name##_topic_array,	\
	};

#ifdef __cplusplus
}
#endif
#endif /* _MROS_TOPIC_CONNECTOR_CIMPL_H_ */
