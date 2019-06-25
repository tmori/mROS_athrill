#ifndef _MROS_COMM_TCP_SERVER_CIMPL_H_
#define _MROS_COMM_TCP_SERVER_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_comm_tcp_client_cimpl.h"

typedef struct {
	mRosCommSocketType socket;
} mRosCommTcpServerType;

extern mRosReturnType mros_comm_tcp_server_init(mRosCommTcpServerType *server);
extern mRosReturnType mros_comm_tcp_server_bind(mRosCommTcpServerType *server, mros_int32 port);
#define MROS_COMM_TCP_SERVER_LISTEN_MAX_DEFAULT_VALUE	1
extern mRosReturnType mros_comm_tcp_server_listen(mRosCommTcpServerType *server, mros_int32 max);
extern mRosReturnType mros_comm_tcp_server_accept(mRosCommTcpServerType *server, mRosCommTcpClientType *client);

#ifdef __cplusplus
}
#endif

#endif /* _MROS_COMM_TCP_SERVER_CIMPL_H_ */
