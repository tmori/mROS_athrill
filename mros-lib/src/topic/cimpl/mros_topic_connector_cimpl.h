#ifndef _MROS_TOPIC_CONNECTOR_CIMPL_H_
#define _MROS_TOPIC_CONNECTOR_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_types.h"
#include "mros_memory.h"
#include "mros_comm_tcp_client_factory_cimpl.h"

typedef struct {
	mRosTopicIdType				topic_id;
	mRosNodeIdType				node_id;
	mRosFuncIdType				func_id;
} mRosTopicConnectorType;

typedef struct {
	mRosTopicConnectorType				value;
	mRosSizeType						queue_maxsize;
	mRosMemoryListHeadType 				queue_head;
	mRosMemoryManagerType				*mempool;
	mRosCommTcpClientListReqEntryType	*commp;
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
extern mRosContainerObjType mros_topic_connector_get_topic_obj(mRosTopicConnectorManagerType *mgrp, mRosTopicIdType topic_id);

extern mRosContainerObjType mros_topic_connector_get_first(mRosTopicConnectorManagerType *mgrp, mRosContainerObjType topic_obj);
extern mRosContainerObjType mros_topic_connector_get_next(mRosTopicConnectorManagerType *mgrp, mRosContainerObjType topic_obj, mRosContainerObjType obj);


extern mRosReturnType mros_topic_connector_get_topic(mRosContainerObjType topic_obj, mRosTopicIdType *topic_id);
extern mRosReturnType mros_topic_connector_get(mRosContainerObjType obj, mRosTopicConnectorType *connector);
extern mRosContainerObjType mros_topic_connector_get_obj(mRosTopicConnectorManagerType *mgrp, mRosTopicConnectorType *connector);

extern mRosReturnType mros_topic_connector_get_connection(mRosContainerObjType obj, mRosCommTcpClientListReqEntryType **connection);
extern mRosReturnType mros_topic_connector_set_connection(mRosContainerObjType obj, mRosCommTcpClientListReqEntryType *connection);

extern mRosReturnType mros_topic_connector_add(mRosTopicConnectorManagerType *mgrp, mRosTopicConnectorType *connector, mRosSizeType queue_length, mRosMemoryManagerType *mempool);
extern mRosReturnType mros_topic_connector_remove(mRosTopicConnectorManagerType *mgrp, mRosTopicConnectorType *connector);


extern mRosReturnType mros_topic_connector_put_data(mRosContainerObjType obj, const char *data, mRosSizeType len);
extern mRosReturnType mros_topic_connector_send_data(mRosContainerObjType obj, const char *data, mRosSizeType len);
extern mRosMemoryListEntryType *mros_topic_connector_receive_data(mRosContainerObjType obj);

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