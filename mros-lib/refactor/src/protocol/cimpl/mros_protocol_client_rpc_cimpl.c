#include "mros_protocol_client_rpc_cimpl.h"
#include "mros_packet_encoder_cimpl.h"
#include "mros_packet_decoder_cimpl.h"
#include "mros_config.h"

static mRosReturnType mros_rpc_sendreply_xmlpacket(mRosEncodeArgType *arg, mRosCommTcpClientType *client, mRosRegisterTopicReqType *req, mRosRegisterTopicResType *res)
{
	mRosReturnType ret;
	mros_boolean is_end;
	mRosSizeType rlen;

	ret = mros_packet_encode(&arg, &req->req_packet);
	if (ret != MROS_E_OK) {
		return ret;
	}

	ret = mros_comm_tcp_client_send_all(client, req->req_packet->data, req->req_packet->data_size, &rlen);
	if (ret != MROS_E_OK) {
		return ret;
	}
	res->reply_packet->data_size = 0;
	do {
		ret = mros_comm_tcp_client_receive(client, &res->reply_packet->data[res->reply_packet->data_size], (res->reply_packet->total_size - res->reply_packet->data_size),  &rlen);
		if (ret != MROS_E_OK) {
			return ret;
		}
		res->reply_packet->data_size += res;
		if (res->reply_packet->data_size >= res->reply_packet->total_size) {
			return MROS_E_NOMEM;
		}
		is_end = mros_packet_has_response_end(res->reply_packet);
	} while (is_end == MROS_FALSE);
	res->result = MROS_E_OK;
	return MROS_E_OK;
}

mRosReturnType mros_rpc_register_publisher(mRosCommTcpClientType *client, mRosRegisterTopicReqType *req, mRosRegisterTopicResType *res)
{
	mRosEncodeArgType arg;

	arg.type = MROS_PACKET_DATA_REGISTER_PUBLISHER_REQ;
	arg.args_int = 1;
	arg.argi[0] = req->node_id;

	arg.args_char = 4;
	arg.argv[0] = "registerPublisher";
	arg.argv[1] = req->topic_name;
	arg.argv[2] = req->topic_typename;
	arg.argv[3] = MROS_URI_SLAVE;
	return mros_rpc_sendreply_xmlpacket(&arg, client, req, res);
}

mRosReturnType mros_rpc_register_subscriber(mRosCommTcpClientType *client, mRosRegisterTopicReqType *req, mRosRegisterTopicResType *res)
{
	mRosEncodeArgType arg;

	arg.type = MROS_PACKET_DATA_REGISTER_SUBSCRIBER_REQ;
	arg.args_int = 1;
	arg.argi[0] = req->node_id;

	arg.args_char = 4;
	arg.argv[0] = "registerSubscriber";
	arg.argv[1] = req->topic_name;
	arg.argv[2] = req->topic_typename;
	arg.argv[3] = MROS_URI_SLAVE;
	return mros_rpc_sendreply_xmlpacket(&arg, client, req, res);
}

mRosReturnType mros_rpc_request_topic(mRosCommTcpClientType *client, mRosRequestTopicReqType *req, mRosRequestTopicResType *res)
{
	mRosEncodeArgType arg;

	arg.type = MROS_PACKET_DATA_REQUEST_TOPIC_REQ;
	arg.args_int = 1;
	arg.argi[0] = req->node_id;

	arg.args_char = 3;
	arg.argv[0] = "requestTopic";
	arg.argv[1] = req->topic_name;
	arg.argv[2] = "TCPROS";

	return mros_rpc_sendreply_xmlpacket(&arg, client, req, res);
}

static mRosReturnType mros_rpc_sendreply_tcpros(mRosEncodeArgType *arg, mRosCommTcpClientType *client, mRosRegisterTopicReqType *req, mRosRegisterTopicResType *res)
{
	mRosPacketType packet;
	mRosReturnType ret;
	mros_boolean is_end;
	mRosSizeType len;
	mRosSizeType rlen;
	mros_int8 rawdata[MROS_TOPIC_RAWDATA_HEADER_SIZE];

	ret = mros_packet_encode(&arg, &req->req_packet);
	if (ret != MROS_E_OK) {
		return ret;
	}

	ret = mros_comm_tcp_client_send_all(client, req->req_packet->data, req->req_packet->data_size, &rlen);
	if (ret != MROS_E_OK) {
		return ret;
	}

	ret = mros_comm_tcp_client_receive_all(&client->socket, rawdata, MROS_TOPIC_RAWDATA_HEADER_SIZE, &rlen);
	if (ret != MROS_E_OK) {
		return NULL;
	}
	packet.total_size = MROS_TOPIC_RAWDATA_HEADER_SIZE;
	packet.data_size = MROS_TOPIC_RAWDATA_HEADER_SIZE;
	packet.data = rawdata;
	ret = mros_packet_get_body_size(&packet, &len);
	if (ret != MROS_E_OK) {
		return ret;
	}
	ret = mros_comm_tcp_client_receive_all(&client->socket, res->reply_packet->data, len, &rlen);
	if (ret != MROS_E_OK) {
		return ret;
	}
	res->result = MROS_E_OK;
	return MROS_E_OK;
}

mRosReturnType mros_rpc_tcpros(mRosCommTcpClientType *client, mRosRcpRosReqType *req, mRosTcpRosResType *res)
{
	mRosEncodeArgType arg;

	arg.type = MROS_PACKET_DATA_TCPROS_PUB_REQ;
	arg.args_int = 1;
	arg.argi[0] = req->node_id;

	arg.args_char = 2;
	arg.argv[0] = req->topic_name;
	arg.argv[1] = req->topic_typename;;

	return mros_rpc_sendreply_tcpros(&arg, client, req, res);
	return MROS_E_OK;
}
