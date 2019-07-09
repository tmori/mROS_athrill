#include "mros_protocol_server_proc_cimpl.h"
#include "mros_comm_tcp_client_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"
#include "mros_sys_config.h"
#include "mros_packet_config.h"
#include "mros_packet_encoder_cimpl.h"
#include "mros_packet_decoder_cimpl.h"
#include "mros_node_cimpl.h"
#include "mros_protocol_operation_cimpl.h"
#include <string.h>

static mRosPacketDecodedRequestType mros_proc_slave_decoded_requst MROS_MATTR_BSS_NOCLR;

mRosReturnType mros_proc_init(void)
{
	return MROS_E_OK;
}

mRosReturnType mros_proc_receive(mRosCommTcpClientType *client, mRosPacketType *packet)
{
	mRosReturnType ret;
	mRosSizeType res;
	mros_boolean is_end;

	packet->data_size = 0;
	do {
		ret = mros_comm_tcp_client_receive(client, &packet->data[packet->data_size], (packet->total_size - packet->data_size),  &res);
		if (ret != MROS_E_OK) {
			ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
			break;
		}
		packet->data_size += res;
		if ((packet->data_size + 1) >= packet->total_size) {
			ret = MROS_E_NOMEM;
			ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
			break;
		}
		is_end = mros_xmlpacket_has_request_end(packet);
	} while (is_end == MROS_FALSE);
	packet->data[packet->data_size] = '\0';
	return ret;
}
mRosReturnType mros_proc_tcpros_receive(mRosCommTcpClientType *client, mRosPacketType *packet)
{
	mRosReturnType ret;
	mRosSizeType res;
	mRosPacketType header_packet;
	mros_int8 rawdata[MROS_TCPROS_RAWDATA_HEADER_SIZE];

	ret = mros_comm_tcp_client_receive_all(client, rawdata, MROS_TCPROS_RAWDATA_HEADER_SIZE, &res);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return ret;
	}

	header_packet.total_size = MROS_TOPIC_RAWDATA_HEADER_SIZE;
	header_packet.data_size = MROS_TOPIC_RAWDATA_HEADER_SIZE;
	header_packet.data = rawdata;
	ret = mros_tcprospacket_get_body_size(&header_packet, &res);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return ret;
	}
	packet->data_size = 0;
	packet->total_size = res;
	ret = mros_comm_tcp_client_receive_all(client, packet->data, packet->total_size, &res);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return ret;
	}
	packet->data_size = res;
	return ret;
}

static mRosNodeIdType mros_publisher_is_exist(mRosTopicIdType topic_id)
{
	mRosContainerObjType obj;
	mRosContainerObjType topic_obj;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_PUB);
	if (mgrp == MROS_NULL) {
		return MROS_ID_NONE;
	}
	topic_obj = mros_topic_connector_get_topic_obj(mgrp, topic_id);
	if (topic_obj == MROS_COBJ_NULL) {
		return MROS_ID_NONE;
	}
	obj = mros_topic_connector_get_first(mgrp, MROS_NODE_TYPE_INNER, topic_obj);
	if (obj != MROS_COBJ_NULL) {
		(void)mros_topic_connector_get(obj, &connector);
		return connector.node_id;
	}
	return MROS_ID_NONE;
}


static mRosReturnType mros_proc_slave_request_topic(mRosCommTcpClientType *client, mRosPacketType *packet)
{
	mRosReturnType ret;
	mRosTopicIdType topic_id;
	mRosSizeType res;

	if (mros_proc_slave_decoded_requst.request.topic.topic_name.res.len >= MROS_TOPIC_NAME_MAXLEN) {
		return MROS_E_INVAL;
	}
	mros_proc_slave_decoded_requst.request.topic.topic_name.res.head[mros_proc_slave_decoded_requst.request.topic.topic_name.res.len] = '\0';
	ret = mros_topic_get((const char*)&mros_proc_slave_decoded_requst.request.topic.topic_name.res.head[0], &topic_id);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return ret;
	}
	mRosNodeIdType node_id = mros_publisher_is_exist(topic_id);
	if (node_id == MROS_ID_NONE) {
		//TODO error reply...
		// original code does not support this case...
	}
	else {
		mRosEncodeArgType arg;
		arg.type = MROS_PACKET_DATA_REQUEST_TOPIC_RES;
		arg.args_int = 1;
		arg.argi[0] = MROS_PUBLISHER_PORT_NO;
		arg.args_char = 2;
		arg.argv[0] ="TCPROS";
		arg.argv[1] = MROS_NODE_IPADDR;
		ret = mros_packet_encode(&arg, packet);
		if (ret != MROS_E_OK) {
			ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
			return ret;
		}
		ret = mros_comm_tcp_client_send_all(client, packet->data, packet->data_size, &res);
	}

	return ret;
}

mRosReturnType mros_proc_slave(mRosCommTcpClientType *client, mRosPacketType *packet)
{
	mRosReturnType ret = MROS_E_INVAL;

	mRosPacketDataEnumType type = mros_xmlpacket_slave_request_decode(packet, &mros_proc_slave_decoded_requst);
	switch (type) {
	case MROS_PACKET_DATA_REQUEST_TOPIC_REQ:
		ret = mros_proc_slave_request_topic(client, packet);
		break;
	default:
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		break;
	}

	return ret;
}

static mRosReturnType mros_proc_add_outersub_connector(mRosCommTcpClientType *client, mRosTopicIdType topic_id)
{
	mRosReturnType ret = MROS_E_INVAL;
	mRosTopicConnectorType connector;
	mRosContainerObjType cobj;
	mRosTopicConnectorManagerType *sub_mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_SUB);
	if (sub_mgrp == MROS_NULL) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return ret;
	}
	connector.topic_id = topic_id;
	connector.func_id = (mRosFuncIdType)MROS_ID_NONE;
	ret = mros_node_create_outer(&connector.node_id);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return MROS_E_NOENT;
	}
	ret = mros_topic_connector_add(sub_mgrp, &connector, MROS_OUTER_CONNECTOR_QUEUE_MAXLEN, MROS_NULL);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return ret;
	}
	cobj = mros_topic_connector_get_obj(sub_mgrp, &connector);

	mRosCommTcpClientListReqEntryType *client_entry = mros_comm_tcp_clientc_alloc_copy(client);
	if (client_entry == MROS_NULL) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, MROS_E_NOENT);
		return MROS_E_NOENT;
	}
	client_entry->data.op.free = mros_protocol_client_obj_free;
	client_entry->data.op.topic_data_receive = mros_protocol_topic_data_receive;
	client_entry->data.op.topic_data_send = mros_protocol_topic_data_send;
	ret = mros_topic_connector_set_connection(cobj, client_entry);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return ret;
	}
	return MROS_E_OK;
}


mRosReturnType mros_proc_pub_tcpros(mRosCommTcpClientType *client, mRosPacketType *packet)
{
	mRosReturnType ret;
	mRosTopicIdType topic_id;
	mRosSizeType res;
	mRosTcpRosPacketType tcpros_packet;

	ret = mros_tcprospacket_decode(packet, &tcpros_packet);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return ret;
	}
	ret = mros_topic_get((const char*)&tcpros_packet.topic[0], &topic_id);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return ret;
	}
	mRosNodeIdType node_id = mros_publisher_is_exist(topic_id);
	if (node_id == MROS_ID_NONE) {
		//TODO error reply...
		// original code does not support this case...
		ROS_ERROR("%s %u : not supported reply error", __FUNCTION__, __LINE__);
	}
	else {
		mRosEncodeArgType arg;
		char *md5sum = "060021388200f6f0f447d0fcd9c64743";//TODO
		arg.type = MROS_PACKET_DATA_TCPROS_TOPIC_RES;
		arg.args_int = 0;
		arg.args_char = 4;
		arg.argv[0] = mros_node_name(node_id);
		arg.argv[1] = mros_topic_get_topic_name(topic_id);
		arg.argv[2] = mros_topic_get_topic_typename(topic_id);
		arg.argv[3] = md5sum;
		ret = mros_packet_encode(&arg, packet);
		if (ret != MROS_E_OK) {
			ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
			return ret;
		}
		ret = mros_comm_tcp_client_send_all(client, packet->data, packet->data_size, &res);
		if (ret != MROS_E_OK) {
			ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
			return ret;
		}
		(void)mros_proc_add_outersub_connector(client, topic_id);
	}

	return ret;
}

