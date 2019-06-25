#include "mros_comm_tcp_server_cimpl.h"

mRosReturnType mros_comm_tcp_server_init(mRosCommTcpServerType *server)
{
	return mros_comm_socket_init(&server->socket, MROS_COMM_SOCKET_TYPE_TCP);
}

mRosReturnType mros_comm_tcp_server_bind(mRosCommTcpServerType *server, mros_int32 port)
{
	mRosReturnType ret;
    mRosSockAddrInType addr;

    mros_comm_inet_local_sockaddr_init(&addr, port);
    ret = mros_comm_bind(server->socket.sock_fd, &addr, sizeof(mRosSockAddrInType));
	if (ret != MROS_E_OK) {
		return MROS_E_SYSERR;
	}
	return MROS_E_OK;
}
mRosReturnType mros_comm_tcp_server_listen(mRosCommTcpServerType *server, mros_int32 max)
{
	mRosReturnType ret;
    if (server->socket.sock_fd < 0) {
		return MROS_E_SYSERR;
    }

    ret = mros_comm_listen(server->socket.sock_fd, max);
    if (ret != MROS_E_OK) {
		return MROS_E_SYSERR;
    }
	return MROS_E_OK;
}

mRosReturnType mros_comm_tcp_server_accept(mRosCommTcpServerType *server, mRosCommTcpClientType *client)
{
	mRosReturnType ret;
	mRosSockAddrInType addr;

    if (server->socket.sock_fd < 0) {
		return MROS_E_SYSERR;
    }
    if (server->socket.blocking == MROS_FALSE) {
    	ret = mros_comm_socket_wait_readable(&server->socket, server->socket.timeout);
    	if (ret != MROS_E_OK) {
    		return ret;
    	}
    }

    mRosSizeType len = sizeof(mRosSockAddrInType);
    client->socket.sock_fd = mros_comm_accept(server->socket.sock_fd, (mRosSockAddrType*)&addr, &len);
    if (client->socket.sock_fd < 0) {
		return MROS_E_SYSERR;
    }
    client->socket.blocking = MROS_TRUE;
    client->socket.timeout = MROS_COMM_DEFAULT_TIMEOUT;
    client->connected = MROS_TRUE;

	return MROS_E_OK;
}
