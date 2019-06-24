#include "mros_comm_socket_cimpl.h"
#include "mros_comm_cimpl.h"
#include <stdlib.h>

mRosReturnType mros_comm_socket_open(mRosCommSocketType *socket, mRosCommSocketEnumType type)
{
	mros_int32 mros_type;

	if (socket->sock_fd < 0) {
		return MROS_E_INVAL;
	}
	switch (type) {
	case MROS_COMM_SOCKET_TYPE_TCP:
		mros_type = MROS_SOCK_STREAM;
		break;
	case MROS_COMM_SOCKET_TYPE_UDP:
		mros_type = MROS_SOCK_DGRAM;
		break;
	default:
		return MROS_E_INVAL;
	}
	socket->sock_fd = mros_comm_socket(MROS_SOCK_AF_INET, mros_type, 0);
    if (socket->sock_fd < 0) {
    	return MROS_E_INVAL;
    }
    socket->blocking = MROS_TRUE;
    socket->timeout = MROS_COMM_DEFAULT_TIMEOUT;
	return MROS_E_OK;
}

mRosReturnType mros_comm_socket_close(mRosCommSocketType *socket)
{
	mros_comm_close(socket->sock_fd);
	socket->sock_fd = -1;
	return MROS_E_OK;
}

static mRosReturnType mros_comm_secket_select(mRosCommSocketType *socket, mros_uint32 timeout, mros_boolean read, mros_boolean write) {

	mRosFdSetType fd_set;
	mRosTimeValType tmo;

	MROS_FD_ZERO(&fd_set);
    MROS_FD_SET(socket->sock_fd, &fd_set);

    mRosFdSetType* r_set = NULL;
    mRosFdSetType* w_set = NULL;

    if (read == MROS_TRUE) {
    	r_set = &fd_set;
    }
    if (write == MROS_TRUE) {
    	w_set = &fd_set;
    }
    mros_comm_set_timeval(timeout, &tmo);
    mRosReturnType ret = mros_comm_select(MROS_FD_SETSIZE, r_set, w_set, NULL, &tmo);
    if ((ret <= 0 || !MROS_FD_ISSET(socket->sock_fd, &fd_set))) {
    	return MROS_E_NOENT;
    }
    return MROS_E_OK;
}


mRosReturnType mros_comm_socket_set_blocking(mRosCommSocketType *socket, mros_boolean blocking, mros_uint32 timeout)
{
	socket->blocking = blocking;
	socket->timeout = timeout;
	return MROS_E_OK;
}


mRosReturnType mros_comm_socket_wait_readable(mRosCommSocketType *socket, mros_uint32 timeout)
{
	return mros_comm_secket_select(socket, timeout, true, false);
}

mRosReturnType mros_comm_socket_wait_writable(mRosCommSocketType *socket, mros_uint32 timeout)
{
	return mros_comm_secket_select(socket, timeout, false, true);
}
