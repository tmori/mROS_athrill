#ifndef _MROS_COMM_TCP_CLIENT_CIMPL_H_
#define _MROS_COMM_TCP_CLIENT_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_comm_socket_cimpl.h"

typedef struct {
	mRosCommSocketType	socket;
	mRosSockAddrInType	remote;
	mros_boolean		connected;
} mRosCommTcpClientType;


extern mRosReturnType mros_comm_tcp_client_init(mRosCommTcpClientType *client);
extern void mros_comm_tcp_client_close(mRosCommTcpClientType *client);
extern mRosReturnType mros_comm_tcp_client_connect(mRosCommTcpClientType *client, const char* host, mros_int32 port);
extern mRosReturnType mros_comm_tcp_client_connect_ip32(mRosCommTcpClientType *client, mros_uint32 ipaddr, mros_int32 port);
extern mros_boolean mros_comm_tcp_client_is_connected(mRosCommTcpClientType *client);
extern mRosReturnType mros_comm_tcp_client_send(mRosCommTcpClientType *client, const char* data, mRosSizeType length, mRosSizeType *res);
extern mRosReturnType mros_comm_tcp_client_send_all(mRosCommTcpClientType *client, const char* data, mRosSizeType length, mRosSizeType *res);
extern mRosReturnType mros_comm_tcp_client_receive(mRosCommTcpClientType *client, char* data, mRosSizeType length, mRosSizeType *res);
extern mRosReturnType mros_comm_tcp_client_receive_all(mRosCommTcpClientType *client, char* data, mRosSizeType length, mRosSizeType *res);


#ifdef __cplusplus
}
#endif

#endif /* _MROS_COMM_TCP_CLIENT_CIMPL_H_ */
