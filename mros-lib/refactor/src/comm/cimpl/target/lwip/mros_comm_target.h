#ifndef _MROS_COMM_TARGET_H_
#define _MROS_COMM_TARGET_H_

#ifdef __cplusplus
extern "C" {
#endif

#if 0
#include "mros_types.h"
#include "lwip/sockets.h"

typedef sockaddr 			mRosSockAddrType;
typedef struct sockaddr_in	mRosSockAddrInType;
typedef struct hostent 		mRosHostEntType;
typedef ip_addr_t 			mRosIpAaddrType;
typedef fd_set				mRosFdSetType;
typedef struct timeval		mRosTimeValType;

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

#endif

#ifdef __cplusplus
}
#endif


#endif /* _MROS_COMM_TARGET_H_ */
