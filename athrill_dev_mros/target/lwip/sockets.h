#ifndef _MROS_SOCKET_H_
#define _MROS_SOCKET_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
typedef unsigned int ip_addr_t;

void lwip_init(void);

void lwip_socket_init(void);

int lwip_accept(int s, struct sockaddr *addr, socklen_t *addrlen);

int lwip_bind(int s, const struct sockaddr *name, socklen_t namelen);
int lwip_shutdown(int s, int how);
int lwip_getpeername (int s, struct sockaddr *name, socklen_t *namelen);
int lwip_getsockname (int s, struct sockaddr *name, socklen_t *namelen);
int lwip_getsockopt (int s, int level, int optname, void *optval, socklen_t *optlen);
int lwip_setsockopt (int s, int level, int optname, const void *optval, socklen_t optlen);
int lwip_close(int s);

int lwip_connect(int s, const struct sockaddr *name, socklen_t namelen);

int lwip_listen(int s, int backlog);

int lwip_recv(int s, void *mem, size_t len, int flags);

int lwip_read(int s, void *mem, size_t len);
int lwip_recvfrom(int s, void *mem, size_t len, int flags,
      struct sockaddr *from, socklen_t *fromlen);
int lwip_send(int s, const void *dataptr, size_t size, int flags);
int lwip_sendto(int s, const void *dataptr, size_t size, int flags,
    const struct sockaddr *to, socklen_t tolen);
int lwip_socket(int domain, int type, int protocol);
int lwip_write(int s, const void *dataptr, size_t size);

int lwip_select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
                struct timeval *timeout);
int lwip_ioctl(int s, long cmd, void *argp);
int lwip_fcntl(int s, int cmd, int val);
struct hostent *lwip_gethostbyname(const char *name);
char *ipaddr_ntoa_r(const ip_addr_t *addr, char *buf, int buflen);

#ifndef __cplusplus
#define true 1
#define false 0
#endif

#endif /* _MROS_SOCKET_H_ */
