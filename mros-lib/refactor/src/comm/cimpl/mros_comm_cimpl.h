#ifndef _MROS_COMM_CIMPL_H_
#define _MROS_COMM_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_types.h"


extern void mros_comm_inet_local_sockaddr_init(mRosSockAddrInType *addr, mros_int32 port);
extern void mros_comm_inet_remote_sockaddr_init(mRosSockAddrInType *addr, mros_int32 port, const char* ipaddrp);
extern void mros_comm_timeval_set(mros_uint32 sec, mros_uint32 usec, mRosTimeValType *tv);

extern void mros_comm_init(void);
extern mros_int32 mros_comm_accept(mros_int32 s, mRosSockAddrType *addr, mRosSizeType addrlen);
extern mros_int32 mros_comm_bind(mros_int32 s, const mRosSockAddrType *name, mRosSizeType namelen);
extern mros_int32 mros_comm_shutdown(mros_int32 s, mros_int32 how);
extern mros_int32 mros_comm_getpeername (mros_int32 s, mRosSockAddrType *name, mRosSizeType *namelen);
extern mros_int32 mros_comm_getsockname (mros_int32 s, mRosSockAddrType *name, mRosSizeType *namelen);
extern mros_int32 mros_comm_getsockopt (mros_int32 s, mros_int32 level, mros_int32 optname, void *optval, mRosSizeType *optlen);
extern mros_int32 mros_comm_setsockopt (mros_int32 s, mros_int32 level, mros_int32 optname, const void *optval, mRosSizeType optlen);
extern mros_int32 mros_comm_close(mros_int32 s);
extern mros_int32 mros_comm_connect(mros_int32 s, const mRosSockAddrType *name, mRosSizeType namelen);
extern mros_int32 mros_comm_listen(mros_int32 s, mros_int32 backlog);
extern mros_int32 mros_comm_recv(mros_int32 s, void *mem, mRosSizeType len, mros_int32 flags);
extern mros_int32 mros_comm_read(mros_int32 s, void *mem, mRosSizeType len);
extern mros_int32 mros_comm_recvfrom(mros_int32 s, void *mem, mRosSizeType len, mros_int32 flags, mRosSockAddrType *from, mRosSizeType *fromlen);
extern mros_int32 mros_comm_send(mros_int32 s, const void *dataptr, mRosSizeType size, mros_int32 flags);
extern mros_int32 mros_comm_sendto(mros_int32 s, const void *dataptr, mRosSizeType size, mros_int32 flags, const mRosSockAddrType *to, mRosSizeType tolen);
extern mros_int32 mros_comm_socket(mros_int32 domain, mros_int32 type, mros_int32 protocol);
extern mros_int32 mros_comm_write(mros_int32 s, const void *dataptr, mRosSizeType size);
extern mros_int32 mros_comm_select(mros_int32 maxfdp1, mRosFdSetType *readset, mRosFdSetType *writeset, mRosFdSetType *exceptset, mRosTimeValType *timeout);
extern mros_int32 mros_comm_ioctl(mros_int32 s, mros_int32 cmd, void *argp);
extern mros_int32 mros_comm_fcntl(mros_int32 s, mros_int32 cmd, int val);
extern mRosHostEntType *mros_comm_gethostbyname(const char *name);
extern char *mros_comm_ipaddr_ntoa_r(const mRosIpAaddrType *addr, char *buf, mRosSizeType buflen);

#ifdef __cplusplus
}
#endif


#endif /* _MROS_COMM_CIMPL_H_ */
