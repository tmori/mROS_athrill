#ifndef _MROS_PROTOCOL_SERVER_PROC_CIMPL_H_
#define _MROS_PROTOCOL_SERVER_PROC_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_types.h"
#include "mros_packet_cimpl.h"
#include "mros_comm_tcp_client_cimpl.h"

extern mRosReturnType mros_proc_init(void);
extern mRosReturnType mros_proc_receive(mRosCommTcpClientType *client, mRosPacketType *packet);
extern mRosReturnType mros_proc_slave(mRosCommTcpClientType *client, mRosPacketType *packet);
extern mRosReturnType mros_proc_pub(mRosCommTcpClientType *client, mRosPacketType *packet);


#ifdef __cplusplus
}
#endif
#endif /* _MROS_PROTOCOL_SERVER_PROC_CIMPL_H_ */
