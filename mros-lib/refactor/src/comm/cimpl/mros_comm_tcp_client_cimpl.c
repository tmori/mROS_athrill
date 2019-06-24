#include "mros_comm_tcp_client_cimpl.h"

mRosReturnType mros_comm_tcp_client_init(mRosCommTcpClientType *client)
{
	client->connected = MROS_FALSE;
	return mros_comm_socket_open(&client->socket, MROS_COMM_SOCKET_TYPE_TCP);
}


mRosReturnType mros_comm_tcp_client_connect(mRosCommTcpClientType *client, const char* host, mros_int32 port)
{
	mRosReturnType ret;
	mRosSockAddrInType addr;

	mros_comm_inet_remote_sockaddr_init(&addr, port, host);

	ret = mros_comm_connect(client->socket.sock_fd, (const struct mRosSockAddr *)&addr, sizeof(mRosSockAddrInType));
	if (ret != MROS_E_OK) {
		(void)mros_comm_socket_close(client->socket.sock_fd);
		return MROS_E_SYSERR;
	}
	client->connected = MROS_TRUE;
	return MROS_E_OK;
}

mros_boolean mros_comm_tcp_client_is_connected(mRosCommTcpClientType *client)
{
	return client->connected;
}
mRosReturnType mros_comm_tcp_client_send(mRosCommTcpClientType *client, const char* data, mRosSizeType length, mRosSizeType *res)
{
	mRosReturnType ret;
	mros_int32 snd_size;

    if ((client->socket.sock_fd < 0) || (client->connected == MROS_FALSE)) {
        return MROS_E_INVAL;
    }

    if (client->socket.blocking == MROS_FALSE) {
    	ret = mros_comm_socket_wait_writable(&client->socket, client->socket.timeout);
    	if (ret != MROS_E_OK) {
    		return ret;
    	}
    }
    snd_size = mros_comm_send(client->socket.sock_fd, data, length, 0);
    if (snd_size == 0) {
		(void)mros_comm_socket_close(client->socket.sock_fd);
		client->connected = MROS_FALSE;
    }
    *res = snd_size;
	return MROS_E_OK;
}
mRosReturnType mros_comm_tcp_client_send_all(mRosCommTcpClientType *client, const char* data, mRosSizeType length, mRosSizeType *res)
{
	mRosReturnType ret;
    mros_int32 writtenLen = 0;

    if ((client->socket.sock_fd < 0) || (client->connected == MROS_FALSE)) {
        return MROS_E_INVAL;
    }

    while (writtenLen < length) {
        if (client->socket.blocking == MROS_FALSE) {
        	ret = mros_comm_socket_wait_writable(&client->socket, client->socket.timeout);
        	if (ret != MROS_E_OK) {
        		return ret;
        	}
        }

        mros_int32 retlen = mros_comm_send(client->socket.sock_fd, data + writtenLen, length - writtenLen, 0);
        if (retlen > 0) {
            writtenLen += retlen;
            continue;
        } else if (retlen == 0) {
    		(void)mros_comm_socket_close(client->socket.sock_fd);
    		client->connected = MROS_FALSE;
            *res = writtenLen;
            return MROS_E_SYSERR;
        } else {
            *res = writtenLen;
            return MROS_E_SYSERR;
        }
    }
    *res = writtenLen;
	return MROS_E_OK;
}
mRosReturnType mros_comm_tcp_client_receive(mRosCommTcpClientType *client, const char* data, mRosSizeType length, mRosSizeType *res)
{
	mRosReturnType ret;
	mros_int32 rcv_size;

    if ((client->socket.sock_fd < 0) || (client->connected == MROS_FALSE)) {
        return MROS_E_INVAL;
    }
    if (client->socket.blocking == MROS_FALSE) {
    	ret = mros_comm_socket_wait_readable(&client->socket, client->socket.timeout);
    	if (ret != MROS_E_OK) {
    		return ret;
    	}
    }
    rcv_size = mros_comm_recv(client->socket.sock_fd, data, length, 0);
    if (rcv_size == 0) {
		(void)mros_comm_socket_close(client->socket.sock_fd);
		client->connected = MROS_FALSE;
    }
    *res = rcv_size;

	return MROS_E_OK;
}

mRosReturnType mros_comm_tcp_client_receive_all(mRosCommTcpClientType *client, const char* data, mRosSizeType length, mRosSizeType *res)
{
	mRosReturnType ret;
    mros_int32 readLen = 0;

    if ((client->socket.sock_fd < 0) || (client->connected == MROS_FALSE)) {
        return MROS_E_INVAL;
    }

    while (readLen < length) {
        if (client->socket.blocking == MROS_FALSE) {
        	ret = mros_comm_socket_wait_writable(&client->socket, client->socket.timeout);
        	if (ret != MROS_E_OK) {
        		return ret;
        	}
        }
        mros_int32 retlen = mros_comm_recv(client->socket.sock_fd, data + readLen, length - readLen, 0);
        if (retlen > 0) {
        	readLen += retlen;
            continue;
        } else if (retlen == 0) {
    		(void)mros_comm_socket_close(client->socket.sock_fd);
    		client->connected = MROS_FALSE;
            *res = readLen;
            return MROS_E_SYSERR;
        } else {
            *res = readLen;
            return MROS_E_SYSERR;
        }
    }
    *res = readLen;
	return MROS_E_OK;
}
