#ifndef _MROS_PROTOCOL_CLIENT_RPC_CIMPL_H_
#define _MROS_PROTOCOL_CLIENT_RPC_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_types.h"
#include "mros_packet_cimpl.h"
#include "mros_comm_tcp_client_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"

typedef struct {
	mRosTopicConnectorEnumType	type;
	mRosNodeIdType				node_id;
	const char*					topic_name;
	const char*					topic_typename;
	mRosPacketType 				*req_packet;
} mRosRegisterTopicReqType;

typedef struct {
	mRosReturnType 		result;
	mRosPacketType 		*reply_packet;
} mRosRegisterTopicResType;
extern mRosReturnType mros_rpc_register_publisher(mRosCommTcpClientType *client, mRosRegisterTopicReqType *req, mRosRegisterTopicResType *res);
extern mRosReturnType mros_rpc_register_subscriber(mRosCommTcpClientType *client, mRosRegisterTopicReqType *req, mRosRegisterTopicResType *res);

typedef struct {
	mRosNodeIdType		node_id;
	const char*			topic_name;
	mRosPacketType 		*req_packet;
} mRosRequestTopicReqType;

typedef struct {
	mRosReturnType 		result;
	mRosPacketType 		*reply_packet;
} mRosRequestTopicResType;
extern mRosReturnType mros_rpc_request_topic(mRosCommTcpClientType *client, mRosRequestTopicReqType *req, mRosRequestTopicResType *res);


#ifdef __cplusplus
}
#endif
#endif /* _MROS_PROTOCOL_CLIENT_RPC_CIMPL_H_ */
