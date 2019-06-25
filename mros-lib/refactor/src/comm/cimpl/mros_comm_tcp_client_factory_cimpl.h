#ifndef _MROS_COMM_TCP_CLIENT_FACTORY_CIMPL_H_
#define _MROS_COMM_TCP_CLIENT_FACTORY_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_list.h"
#include "mros_config.h"
#include "mros_comm_tcp_client_cimpl.h"
#include "mros_wait_queue.h"

typedef struct {
	mRosTopicIdType 		topic_id;
	mros_uint32				ipaddr;
	mros_int32				port;
	mRosWaitListEntryType	waitobj;
} mRosRquestObjectType;

typedef struct {
	mRosReturnType (*topic_data_send) (mRosCommTcpClientType *client, mRosMemoryManagerType *mempool, const char *data, mRosSizeType datalen);
	mRosMemoryListEntryType* (*topic_data_receive) (mRosCommTcpClientType *client, mRosMemoryManagerType *mempool);
	void (*free) (void* reqp);
} mRosCommOperationType;

typedef struct {
	mRosCommTcpClientType 	client;
	mRosCommOperationType	op;
	mRosRquestObjectType	reqobj;
} mRosCommTcpClientReqEntryType;
typedef ListEntryType(mRosCommTcpClientListReqEntryType, mRosCommTcpClientReqEntryType) mRosCommTcpClientListReqEntryType;
typedef ListHeadType(mRosCommTcpClientListReqEntryType) mRosCommTcpClientEntryHeadType;

extern mRosReturnType mros_comm_tcp_client_factory_init(void);
extern mRosCommTcpClientListReqEntryType *mros_comm_tcp_clientc_alloc(void);
extern void mros_comm_tcp_clientc_free(mRosCommTcpClientListReqEntryType *client);


#ifdef __cplusplus
}
#endif

#endif /* _MROS_COMM_TCP_CLIENT_FACTORY_CIMPL_H_ */
