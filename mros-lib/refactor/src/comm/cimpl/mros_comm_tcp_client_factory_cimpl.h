#ifndef _MROS_COMM_TCP_CLIENT_FACTORY_CIMPL_H_
#define _MROS_COMM_TCP_CLIENT_FACTORY_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_list.h"
#include "mros_config.h"
#include "mros_comm_tcp_client_cimpl.h"

typedef struct {
	mRosTopicIdType 		topic_id;
	mRosCommTcpClientType 	client;
} mRosCommTcpClientEntryType;
typedef ListEntryType(mRosCommTcpClientListEntryType, mRosCommTcpClientEntryType) mRosCommTcpClientListEntryType;
typedef ListHeadType(mRosCommTcpClientListEntryType) mRosCommTcpClientEntryHeadType;

extern mRosReturnType mros_comm_tcp_client_factory_init(void);
extern mRosCommTcpClientListEntryType *mros_comm_tcp_clientc_alloc(void);
extern void mros_comm_tcp_clientc_free(mRosCommTcpClientListEntryType *client);


#ifdef __cplusplus
}
#endif

#endif /* _MROS_COMM_TCP_CLIENT_FACTORY_CIMPL_H_ */
