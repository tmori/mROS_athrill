#ifndef _MROS_COMM_TCP_SERVER_CIMPL_H_
#define _MROS_COMM_TCP_SERVER_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_comm_tcp_client_cimpl.h"

typedef struct {
	mRosCommSocketType socket;
} mRosCommTcpServerType;

extern mRosReturnType mros_comm_tcp_server_bind(mRosCommTcpServerType *server, mros_int32 port);
extern mRosReturnType mros_comm_tcp_server_listen(mRosCommTcpServerType *server, mros_int32 backlog);
extern mRosReturnType mros_comm_tcp_server_accept(mRosCommTcpServerType *server, mRosCommTcpClientType *client);

#ifdef __cplusplus
}
#endif

#endif /* _MROS_COMM_TCP_SERVER_CIMPL_H_ */
