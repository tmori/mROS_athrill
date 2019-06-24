#ifndef _MROS_COMM_TARGET_H_
#define _MROS_COMM_TARGET_H_

#ifdef __cplusplus
extern "C" {
#endif

#if 1
#include "mros_types.h"
#include "lwip/sockets.h"

typedef sockaddr 			mRosSockAddrType;
typedef struct sockaddr_in	mRosSockAddrInType;
typedef struct hostent 		mRosHostEntType;
typedef ip_addr_t 			mRosIpAaddrType;
typedef fd_set				mRosFdSetType;
typedef struct timeval		mRosTimeValType;

#define MROS_FD_ZERO(arg)				FD_ZERO(arg)
#define MROS_FD_SET(arg1, arg2)			FD_SET(arg1, arg2)
#define MROS_FD_SETSIZE					FD_SETSIZE
#define MROS_FD_ISSET(arg1, arg2)		FD_ISSET(arg1, arg2)

#define MROS_SOCK_STREAM     SOCK_STREAM
#define MROS_SOCK_DGRAM      SOCK_DGRAM
#define MROS_SOCK_RAW        SOCK_RAW

#define MROS_SOCK_UNSPEC	AF_UNSPEC
#define MROS_SOCK_AF_INET	AF_INET

#else
/*
 * for test stub
 */
#include "mros_types.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>

typedef mros_uint32 ip_addr_t;

typedef sockaddr 			mRosSockAddrType;
typedef struct sockaddr_in	mRosSockAddrInType;
typedef struct hostent 		mRosHostEntType;
typedef ip_addr_t 			mRosIpAaddrType;
typedef fd_set				mRosFdSetType;
typedef struct timeval		mRosTimeValType;

#define MROS_FD_ZERO(arg)				FD_ZERO(arg)
#define MROS_FD_SET(arg1, arg2)			FD_SET(arg1, arg2)
#define MROS_FD_SETSIZE					FD_SETSIZE
#define MROS_FD_ISSET(arg1, arg2)		FD_ISSET(arg1, arg2)

#define MROS_SOCK_STREAM     SOCK_STREAM
#define MROS_SOCK_DGRAM      SOCK_DGRAM
#define MROS_SOCK_RAW        SOCK_RAW

#define MROS_SOCK_UNSPEC	AF_UNSPEC
#define MROS_SOCK_AF_INET	AF_INET

#endif

#ifdef __cplusplus
}
#endif


#endif /* _MROS_COMM_TARGET_H_ */
