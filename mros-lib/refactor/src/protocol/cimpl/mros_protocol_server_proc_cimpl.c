#include "mros_protocol_server_proc_cimpl.h"
#include "mros_comm_tcp_client_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"
#include "mros_config.h"

static char *topic_name_buffer[MROS_TOPIC_NAME_MAXLEN];

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
			break;
		}
		packet->data_size += res;
		if (packet->data_size >= packet->total_size) {
			ret = MROS_E_NOMEM;
			break;
		}
		is_end = mros_packet_has_request_end(packet);
	} while (is_end == MROS_FALSE);

	return ret;
}
mRosReturnType mros_proc_tcpros_receive(mRosCommTcpClientType *client, mRosPacketType *packet)
{
	mRosReturnType ret;
	mRosSizeType res;
	mros_boolean is_end;
	mRosPacketType header_packet;
	mros_int8 rawdata[MROS_TCPROS_RAWDATA_HEADER_SIZE];

	ret = mros_comm_tcp_client_receive_all(&client->socket, rawdata, MROS_TCPROS_RAWDATA_HEADER_SIZE, &res);
	if (ret != MROS_E_OK) {
		return ret;
	}

	header_packet.total_size = MROS_TOPIC_RAWDATA_HEADER_SIZE;
	header_packet.data_size = MROS_TOPIC_RAWDATA_HEADER_SIZE;
	header_packet.data = rawdata;
	ret = mros_packet_get_body_size(&packet, &res);
	if (ret != MROS_E_OK) {
		return ret;
	}
	packet->data_size = 0;
	packet->total_size = res;
	ret = mros_comm_tcp_client_receive_all(&client->socket, &packet->data, packet->total_size, &res);
	if (ret != MROS_E_OK) {
		return ret;
	}
	return ret;
}

static mRosNodeIdType mros_publisher_is_exist(mRosTopicIdType topic_id)
{
	mRosContainerObjType obj;
	mRosContainerObjType topic_obj;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_PUB);
	if (mgrp == NULL) {
		return MROS_ID_NONE;
	}
	topic_obj = mros_topic_connector_get_topic_obj(mgrp, topic_id);
	if (topic_obj == MROS_COBJ_NULL) {
		return MROS_ID_NONE;
	}
	obj = mros_topic_connector_get_first(mgrp, topic_obj);
	while (obj != MROS_COBJ_NULL) {
		(void)mros_topic_connector_get(obj, &connector);
		mRosNodeEnumType type = mros_node_type(connector.node_id);
		if (type == ROS_NODE_TYPE_INNER) {
			return connector.node_id;
		}
		obj = mros_topic_connector_get_next(mgrp, topic_obj, obj);
	}
	return MROS_ID_NONE;
}


static mRosReturnType mros_proc_slave_request_topic(mRosCommTcpClientType *client, mRosPacketType *packet)
{
	mRosReturnType ret;
	mRosTopicIdType topic_id;
	mRosSizeType res;

	ret = mros_packet_reqtopic_get_topic_name(packet, topic_name_buffer, MROS_TOPIC_NAME_MAXLEN);
	if (ret != MROS_E_OK) {
		return ret;
	}
	ret = mros_topic_get(topic_name_buffer, &topic_id);
	if (ret != MROS_E_OK) {
		return ret;
	}
	mRosNodeIdType node_id = mros_publisher_is_exist(topic_id);
	if (node_id == MROS_ID_NONE) {
		//TODO error reply...
		// original code does not support this case...
	}
	else {
		ret = mros_packet_encode_request_topic_res(packet, MROS_NODE_IPADDR, MROS_PUBLISHER_PORT_NO);
		if (ret != MROS_E_OK) {
			return ret;
		}
		ret = mros_comm_tcp_client_send_all(client, packet->data, packet->data_size, &res);
	}

	return ret;
}

mRosReturnType mros_proc_slave(mRosCommTcpClientType *client, mRosPacketType *packet)
{
	mRosReturnType ret = MROS_E_INVAL;

	mRosPacketDataType type = mros_packet_get_method(packet);
	switch (type) {
	case MROS_PACKET_DATA_REQUEST_TOPIC_REQ:
		ret = mros_proc_slave_request_topic(client, packet);
		break;
	default:
		//TODO ERRLOG
		break;
	}

	return ret;
}

static mRosReturnType mros_proc_add_outersub_connector(mRosCommTcpClientType *client, mRosTopicIdType topic_id)
{
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosContainerObjType cobj;
	mRosTopicConnectorManagerType *sub_mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_SUB);
	if (sub_mgrp == NULL) {
		return MROS_E_INVAL;
	}
	connector.topic_id = topic_id;
	connector.func_id = (mRosFuncIdType)MROS_ID_NONE;
	ret = mros_node_create_outer(&connector.node_id);
	if (ret != MROS_E_OK) {
		//TODO ERR LOG
		return MROS_E_NOENT;
	}
	ret = mros_topic_connector_add(sub_mgrp, &connector, MROS_OUTER_CONNECTOR_QUEUE_MAXLEN, NULL);
	if (ret != MROS_E_OK) {
		//TODO ERR LOG
		return ret;
	}
	cobj = mros_topic_connector_get_obj(sub_mgrp, &connector);

	mRosCommTcpClientListReqEntryType *client_entry = mros_comm_tcp_clientc_alloc_copy(client);
	if (client_entry == NULL) {
		return MROS_E_NOENT;
	}

	ret = mros_topic_connector_set_connection(cobj, client_entry);
	if (ret != MROS_E_OK) {
		//TODO ERR LOG
		return ret;
	}
	return MROS_E_OK;
}


static mRosReturnType mros_proc_pub_tcpros(mRosCommTcpClientType *client, mRosPacketType *packet)
{
	mRosReturnType ret;
	mRosTopicIdType topic_id;
	mRosSizeType res;

	ret = mros_packet_tcprospub_get_topic_name(packet, topic_name_buffer, MROS_TOPIC_NAME_MAXLEN);
	if (ret != MROS_E_OK) {
		return ret;
	}
	ret = mros_topic_get(topic_name_buffer, &topic_id);
	if (ret != MROS_E_OK) {
		return ret;
	}
	mRosNodeIdType node_id = mros_publisher_is_exist(topic_id);
	if (node_id == MROS_ID_NONE) {
		//TODO error reply...
		// original code does not support this case...
	}
	else {
		//TODO args:node_name, msg_def, topic_name, topic_type, md5sum
		ret = mros_packet_encode_tcpros_topic_res(packet, MROS_NODE_IPADDR, MROS_PUBLISHER_PORT_NO);
		if (ret != MROS_E_OK) {
			return ret;
		}
		ret = mros_comm_tcp_client_send_all(client, packet->data, packet->data_size, &res);
		if (ret != MROS_E_OK) {
			return ret;
		}
		(void)mros_proc_add_outersub_connector(client, topic_id);
	}

	return ret;
}

mRosReturnType mros_proc_pub(mRosCommTcpClientType *client, mRosPacketType *packet)
{
	mRosReturnType ret = MROS_E_INVAL;

	mRosPacketDataType type = mros_packet_get_method(packet);
	switch (type) {
	case MROS_PACKET_DATA_TCPROS_PUB_REQ:
		ret = mros_proc_pub_tcpros(client, packet);
		break;
	default:
		//TODO ERRLOG
		break;
	}

	return ret;
}