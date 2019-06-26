#include "mros_protocol_master_cimpl.h"
#include "mros_protocol_subscribe_cimpl.h"
#include "mros_protocol_client_rpc_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"
#include "mros_config.h"
#include "mros_exclusive_area.h"
#include "mros_wait_queue.h"
#include "mros_comm_tcp_client_cimpl.h"
#include "mros_packet_decoder_cimpl.h"
#include "mros_protocol_operation_cimpl.h"

#include <stdlib.h>

typedef union {
	char buffer;
	char buffer1[MROS_PACKET_MAXSIZE_REQ_REGISTER_PUBLISHER];
	char buffer2[MROS_PACKET_MAXSIZE_RES_REGISTER_PUBLISHER];
	char buffer3[MROS_PACKET_MAXSIZE_REQ_REGISTER_SUBSCRIBER];
	char buffer4[MROS_PACKET_MAXSIZE_RES_REGISTER_SUBSCRIBER];
} mRosMasterPacketRegisterBufferType;

typedef union {
	char buffer;
	char buffer1[MROS_PACKET_MAXSIZE_REQ_REQUEST_TOPIC];
	char buffer1[MROS_PACKET_MAXSIZE_RES_REQUEST_TOPIC];
} mRosMasterPackeReqTopictBufferType;

static mRosMasterPacketRegisterBufferType mros_master_packet_register_buffer;
static mRosMasterPackeReqTopictBufferType mros_master_packet_reqtopic_buffer;

typedef struct {
	mRosProtocolMasterStateEnumType 	state;
	mRosEncodeArgType 					arg;
	mRosPacketType						register_packet;
	mRosPacketType						reqtopic_packet;
	mRosCommTcpClientType				master_comm;
} mRosProtocolMasterType;

static mRosProtocolMasterType mros_protocol_master;
static mRosReturnType mros_protocol_master_register_publisher(mRosProtocolMasterRequestType *pub_req);
static mRosReturnType mros_protocol_master_register_subscriber(mRosProtocolMasterRequestType *sub_req);

mRosReturnType mros_protocol_master_init(void)
{
	mRosReturnType ret = mros_comm_tcp_client_init(&mros_protocol_master.master_comm, MROS_MASTER_IPADDR, MROS_MASTER_PORT_NO);
	if (ret != MROS_E_OK) {
		return ret;
	}
	mros_protocol_master.register_packet.total_size = sizeof(mRosMasterPacketRegisterBufferType);
	mros_protocol_master.register_packet.data = &mros_master_packet_register_buffer.buffer;
	mros_protocol_master.reqtopic_packet.total_size = sizeof(mRosMasterPackeReqTopictBufferType);
	mros_protocol_master.reqtopic_packet.data = &mros_master_packet_reqtopic_buffer.buffer;
	mros_protocol_master.state = MROS_PROTOCOL_MASTER_STATE_WAITING;
	return MROS_E_OK;
}

void mros_protocol_master_run(void)
{
	while (MROS_TRUE) {
		mros_exclusive_lock(&mros_master_exclusive_area);
		mros_server_queue_wait(&mros_master_exclusive_area, &mros_master_wait_queue);
		mRosWaitListEntryType *wait_entry = mros_server_queue_get(&mros_master_wait_queue);
		mros_exclusive_unlock(&mros_master_exclusive_area);

		if (wait_entry == NULL) {
			continue;
		}
		mRosProtocolMasterRequestType *req = (mRosProtocolMasterRequestType*)wait_entry->data.reqp;
		switch (req->req_type) {
		case MROS_PROTOCOL_MASTER_REQ_REGISTER_PUBLISHER:
			mros_protocol_master_register_publisher(req);
			break;
		case MROS_PROTOCOL_MASTER_REQ_REGISTER_SUBSCRIBER:
			mros_protocol_master_register_subscriber(req);
			break;
		default:
			break;
		}
		mros_client_wakeup(wait_entry);
	}
	return;
}

static mRosReturnType mros_protocol_master_register(mRosProtocolMasterRequestType *req, mRosTopicConnectorEnumType type, mRosRegisterTopicResType *rpc_response)
{
	mRosReturnType ret;
	mRosSizeType res;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;
	const char* method;
	mRosRegisterTopicReqType rpc_request;

	mgrp = mros_topic_connector_factory_get(type);
	if (mgrp == NULL) {
		return MROS_E_INVAL;
	}
	ret = mros_topic_connector_get(req->connector_obj,  &connector);
	if (ret != MROS_E_OK) {
		return MROS_E_INVAL;
	}

#if 1
	rpc_response->reply_packet =  &mros_protocol_master.register_packet;

	rpc_request.node_id = connector.node_id;
	rpc_request.req_packet = &mros_protocol_master.register_packet;
	rpc_request.topic_name = mros_topic_get_topic_name(connector.topic_id);
	rpc_request.topic_typename = mros_topic_get_topic_typename(connector.topic_id);
	ret = mros_rpc_register_publisher(&mros_protocol_master.master_comm, &rpc_request, rpc_response);
	if (ret != MROS_E_OK) {
		return ret;
	}
#else
	if (type == MROS_TOPIC_CONNECTOR_PUB) {
		method = "registerPublisher";
	}
	else {
		method = "registerSubscriber";
	}
	mros_protocol_master.arg.args_int = 1;
	mros_protocol_master.arg.argi[0] = connector.node_id;

	mros_protocol_master.arg.args_char = 4;
	mros_protocol_master.arg.argv[0] = method;
	mros_protocol_master.arg.argv[1] = mros_topic_get_topic_name(connector.topic_id);
	mros_protocol_master.arg.argv[2] = mros_topic_get_topic_typename(connector.topic_id);
	mros_protocol_master.arg.argv[3] = MROS_URI_SLAVE;

	ret = mros_packet_encode(&mros_protocol_master.arg, &mros_protocol_master.request_packet);
	if (ret != MROS_E_OK) {
		return ret;
	}

	ret = mros_comm_tcp_client_send_all(&mros_protocol_master.master_comm, mros_protocol_master.request_packet.data, mros_protocol_master.request_packet.data_size, &res);
	if (ret != MROS_E_OK) {
		return ret;
	}
	ret = mros_comm_tcp_client_receive_all(&mros_protocol_master.master_comm, mros_protocol_master.reply_packet.data, mros_protocol_master.reply_packet.data_size, &res);
	if (ret != MROS_E_OK) {
		return ret;
	}
	//TODO sendReply
#endif
	return ret;
}

static mRosReturnType mros_protocol_master_request_topic(mRosProtocolMasterRequestType *req, mRosRequestTopicResType *rpc_response)
{
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;
	mRosRequestTopicReqType rpc_request;
	mros_uint32 ipaddr;
	mros_int32 port;
	mRosPtrType ptr;

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_SUB);
	if (mgrp == NULL) {
		return MROS_E_INVAL;
	}
	ret = mros_topic_connector_get(req->connector_obj,  &connector);
	if (ret != MROS_E_OK) {
		return MROS_E_INVAL;
	}

#if 1
	rpc_response->reply_packet =  &mros_protocol_master.reqtopic_packet;

	rpc_request.node_id = connector.node_id;
	rpc_request.req_packet = &mros_protocol_master.reqtopic_packet;
	rpc_request.topic_name = mros_topic_get_topic_name(connector.topic_id);
	ret = mros_rpc_request_topic(&mros_protocol_master.master_comm, &rpc_request, rpc_response);
	if (ret != MROS_E_OK) {
		return ret;
	}

	//TODO まだ出版ノードが存在しない場合は，非同期でマスタから情報をもらう
	ptr = mros_packet_get_reqtopic_first_uri(rpc_response->reply_packet, &ipaddr, &port);
	while (ptr != NULL) {
		mRosCommTcpClientListReqEntryType *req = mros_comm_tcp_clientc_alloc();
		if (req == NULL) {
			ret = MROS_E_NOMEM;
			//TODO ERR LOG
			goto done;
		}
		req->data.reqobj.ipaddr = ipaddr;
		req->data.reqobj.port = port;
		req->data.reqobj.topic_id = connector.topic_id;
		req->data.op.free = mros_protocol_client_obj_free;
		req->data.op.topic_data_receive = mros_protocol_topic_data_receive;
		req->data.op.topic_data_send = mros_protocol_topic_data_send;
		mros_client_wait_entry_init(&req->data.reqobj.waitobj, req);

		mros_exclusive_lock(&mros_subscribe_exclusive_area);
		mros_server_queue_put(&mros_subscribe_wait_queue, &req->data.reqobj.waitobj);
		mros_server_queue_wakeup(&mros_subscribe_wait_queue);
		mros_exclusive_unlock(&mros_subscribe_wait_queue);

		ptr = mros_packet_get_reqtopic_next_uri(ptr, rpc_response->reply_packet, &ipaddr, &port);
	}

#else
	mros_protocol_master.arg.args_int = 1;
	mros_protocol_master.arg.argi[0] = connector.node_id;

	mros_protocol_master.arg.args_char = 2;
	mros_protocol_master.arg.argv[0] = "requestTopic";
	mros_protocol_master.arg.argv[1] = mros_topic_get_topic_name(connector.topic_id);
	mros_protocol_master.arg.argv[2] = "TCPROS";

	ret = mros_packet_encode(&mros_protocol_master.arg, &mros_protocol_master.request_packet);
	if (ret != MROS_E_OK) {
		return ret;
	}
	//TODO sendReply
#endif
done:
	return ret;
}

static mRosReturnType mros_protocol_master_register_publisher(mRosProtocolMasterRequestType *pub_req)
{
	mRosReturnType ret;
	mRosRegisterTopicResType rpc_response;

	mros_protocol_master.state = MROS_PROTOCOL_MASTER_STATE_REGISTER_PUBLISHER;

	ret = mros_comm_tcp_client_connect(&mros_protocol_master.master_comm);
	if (ret != MROS_E_OK) {
		goto done;
	}
	ret = mros_protocol_master_register(pub_req, MROS_TOPIC_CONNECTOR_PUB, &rpc_response);
	if (ret != MROS_E_OK) {
		goto done;
	}
	ret = mros_packet_get_regpub_result(rpc_response.reply_packet);

	mros_comm_tcp_client_close(&mros_protocol_master.master_comm);

done:
	mros_protocol_master.state = MROS_PROTOCOL_MASTER_STATE_WAITING;

	return ret;
}


static mRosReturnType mros_protocol_master_register_subscriber(mRosProtocolMasterRequestType *sub_req)
{
	mRosReturnType ret;
	mRosRegisterTopicResType rpc_regc_res;
	mRosRequestTopicResType rpc_topic_res;
	mros_uint32 ipaddr;
	mros_int32 port;
	mRosPtrType ptr;

	mros_protocol_master.state = MROS_PROTOCOL_MASTER_STATE_REGISTER_SUBSCRIBER;

	ret = mros_comm_tcp_client_connect(&mros_protocol_master.master_comm);
	if (ret != MROS_E_OK) {
		goto done;
	}

	ret = mros_protocol_master_register(sub_req, MROS_TOPIC_CONNECTOR_SUB, &rpc_regc_res);
	if (ret != MROS_E_OK) {
		goto done;
	}
	mros_comm_tcp_client_close(&mros_protocol_master.master_comm);
	ret = mros_packet_get_regpub_result(rpc_regc_res.reply_packet);
	if (ret != MROS_E_OK) {
		goto done;
	}

	mros_protocol_master.state = MROS_PROTOCOL_MASTER_STATE_REQUESTING_TOPIC;

	//TODO まだ出版ノードが存在しない場合は，非同期でマスタから情報をもらう
	ptr = mros_packet_get_regsub_first_uri(rpc_regc_res.reply_packet, &ipaddr, &port);
	while (ptr != NULL) {
		mRosCommTcpClientType client;

		ret = mros_comm_tcp_client_ip32_init(&client, ipaddr, port);
		if (ret != MROS_E_OK) {
			goto done;
		}
		ret = mros_comm_tcp_client_connect(&client);
		if (ret != MROS_E_OK) {
			goto done;
		}
		ret = mros_protocol_master_request_topic(sub_req, &rpc_topic_res);
		mros_comm_tcp_client_close(&client);
		if (ret != MROS_E_OK) {
			goto done;
		}
		ptr = mros_packet_get_regsub_next_uri(ptr, rpc_regc_res.reply_packet, &ipaddr, &port);
	}

done:
	mros_protocol_master.state = MROS_PROTOCOL_MASTER_STATE_WAITING;

	return ret;
}
