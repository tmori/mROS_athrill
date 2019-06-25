#include "mros_comm_target.h"
#include <string.h>
#include <stdio.h>
#include "mros_comm_cimpl.h"

void mros_comm_inet_local_sockaddr_init(mRosSockAddrInType *addr, mros_int32 port)
{
    memset(addr, 0, sizeof(mRosSockAddrInType));

    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = INADDR_ANY;
	return;
}

void mros_comm_inet_remote_sockaddr_init(mRosSockAddrInType *addr, mros_int32 port, const char* ipaddrp)
{
	mros_uint8 addr_array[5];
    memset(addr, 0, sizeof(mRosSockAddrInType));

    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    (void)sscanf(ipaddrp, "%3u.%3u.%3u.%3u",
    		(mros_uint8*)&addr_array[0],
			(mros_uint8*)&addr_array[1],
			(mros_uint8*)&addr_array[2],
			(mros_uint8*)&addr_array[3]);

    //TODO host entry

    memcpy((void*)&addr->sin_addr.s_addr, (void*)&addr_array, 4U);
	return;
}
void mros_comm_inet_remote_sockaddr_ip32_init(mRosSockAddrInType *addr, mros_int32 port, mros_uint32 ipaddr)
{
    memset(addr, 0, sizeof(mRosSockAddrInType));

    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    memcpy((void*)&addr->sin_addr.s_addr, (void*)&ipaddr, 4U);
	return;
}

void mros_comm_timeval_set(mros_uint32 sec, mros_uint32 usec, mRosTimeValType *tv)
{
	tv->tv_sec = sec;
	tv->tv_usec = usec;
	return;
}


void mros_comm_init(void)
{
	lwip_init();
	return;
}
mros_int32 mros_comm_accept(mros_int32 s, mRosSockAddrType *addr, mRosSizeType addrlen)
{
	return lwip_accept(s, addr, addrlen);
}
mros_int32 mros_comm_bind(mros_int32 s, const mRosSockAddrType *name, mRosSizeType namelen)
{
	return lwip_bind(s, name, namelen);
}
mros_int32 mros_comm_shutdown(mros_int32 s, mros_int32 how)
{
	return lwip_shutdown(s, how);
}
mros_int32 mros_comm_getpeername (mros_int32 s, mRosSockAddrType *name, mRosSizeType *namelen)
{
	return lwip_getpeername(s, name, namelen);
}
mros_int32 mros_comm_getsockname (mros_int32 s, mRosSockAddrType *name, mRosSizeType *namelen)
{
	return lwip_getsockname(s, name, namelen);
}
mros_int32 mros_comm_getsockopt (mros_int32 s, mros_int32 level, mros_int32 optname, void *optval, mRosSizeType *optlen)
{
	return lwip_getsockopt(s, level, optname, optval, optlen);
}
mros_int32 mros_comm_setsockopt (mros_int32 s, mros_int32 level, mros_int32 optname, const void *optval, mRosSizeType optlen)
{
	return lwip_setsockopt(s, level, optname, optval, optlen);
}
mros_int32 mros_comm_close(mros_int32 s)
{
	return lwip_close(s);
}
mros_int32 mros_comm_connect(mros_int32 s, const mRosSockAddrType *name, mRosSizeType namelen)
{
	return lwip_connect(s, name, namelen);
}
mros_int32 mros_comm_listen(mros_int32 s, mros_int32 backlog)
{
	return lwip_listen(s, backlog);
}
mros_int32 mros_comm_recv(mros_int32 s, void *mem, mRosSizeType len, mros_int32 flags)
{
	return lwip_recv(s, mem, len, flags);
}
mros_int32 mros_comm_read(mros_int32 s, void *mem, mRosSizeType len)
{
	return lwip_read(s, mem, len);
}
mros_int32 mros_comm_recvfrom(mros_int32 s, void *mem, mRosSizeType len, mros_int32 flags, mRosSockAddrType *from, mRosSizeType *fromlen)
{
	return lwip_recvfrom(s, mem, len, flags, from, fromlen);
}
mros_int32 mros_comm_send(mros_int32 s, const void *dataptr, mRosSizeType size, mros_int32 flags)
{
	return lwip_send(s, dataptr, size, flags);
}
mros_int32 mros_comm_sendto(mros_int32 s, const void *dataptr, mRosSizeType size, mros_int32 flags, const mRosSockAddrType *to, mRosSizeType tolen)
{
	return lwip_sendto(s, dataptr, size, flags, to, tolen);
}
mros_int32 mros_comm_socket(mros_int32 domain, mros_int32 type, mros_int32 protocol)
{
	return lwip_socket(domain, type, protocol);
}
mros_int32 mros_comm_write(mros_int32 s, const void *dataptr, mRosSizeType size)
{
	return lwip_write(s, dataptr, size);
}
mros_int32 mros_comm_select(mros_int32 maxfdp1, mRosFdSetType *readset, mRosFdSetType *writeset, mRosFdSetType *exceptset, mRosTimeValType *timeout)
{
	return lwip_select(maxfdp1, readset, writeset, exceptset, timeout);
}
mros_int32 mros_comm_ioctl(mros_int32 s, mros_int32 cmd, void *argp)
{
	return lwip_comm_ioctl(s, cmd, argp);
}
mros_int32 mros_comm_fcntl(mros_int32 s, mros_int32 cmd, int val)
{
	return lwip_comm_fcntl(s, cmd, val);
}
mRosHostEntType *mros_comm_gethostbyname(const char *name)
{
	return lwip_gethostbyname(name);
}
char *mros_comm_ipaddr_ntoa_r(const mRosIpAaddrType *addr, char *buf, mRosSizeType buflen)
{
	return lwip_ipaddr_ntoa_r(addr, buf, buflen);
}
