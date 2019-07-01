#ifndef _MROS_PROTOCOL_OPERATION_CIMPL_H_
#define _MROS_PROTOCOL_OPERATION_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_list.h"
#include "mros_config.h"
#include "mros_memory.h"
#include "mros_comm_tcp_client_cimpl.h"

extern mRosReturnType mros_protocol_topic_data_send(mRosCommTcpClientType *client, const char *data, mRosSizeType datalen);
extern mRosMemoryListEntryType* mros_protocol_topic_data_receive(mRosCommTcpClientType *client, mRosMemoryManagerType *mempool);

/*
 * reqp: mRosCommTcpClientListReqEntryType
 */
extern void mros_protocol_client_obj_free(void* reqp);


#ifdef __cplusplus
}
#endif
#endif /* _MROS_PROTOCOL_OPERATION_CIMPL_H_ */
