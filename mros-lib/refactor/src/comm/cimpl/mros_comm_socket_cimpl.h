#ifndef _MROS_COMM_SOCKET_CIMPL_H_
#define _MROS_COMM_SOCKET_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_comm_cimpl.h"

typedef struct {
	mros_int32		sock_fd;
	mros_uint32		timeout;
	mros_boolean	blocking;
} mRosCommSocketType;

typedef enum {
	MROS_COMM_SOCKET_TYPE_TCP = 0,
	MROS_COMM_SOCKET_TYPE_UDP,
	MROS_COMM_SOCKET_TYPE_INNER, //TODO?? 必要か？
} mRosCommSocketEnumType;

extern mRosReturnType mros_comm_socket_open(mRosCommSocketType *socket, mRosCommSocketEnumType type);
extern mRosReturnType mros_comm_socket_close(mRosCommSocketType *socket);
extern mRosReturnType mros_comm_socket_set_blocking(mRosCommSocketType *socket, mros_boolean blocking, mros_uint32 timeout);

extern mRosReturnType mros_comm_wait_readable(mRosCommSocketType *socket, mros_uint32 timeout);
extern mRosReturnType mros_comm_wait_writable(mRosCommSocketType *socket, mros_uint32 timeout);

#ifdef __cplusplus
}
#endif

#endif /* _MROS_COMM_SOCKET_CIMPL_H_ */
