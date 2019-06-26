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

static mros_boolean mros_publisher_is_exist(mRosTopicIdType topic_id)
{
	mRosContainerObjType obj;
	mRosContainerObjType topic_obj;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_PUB);
	if (mgrp == NULL) {
		return MROS_E_INVAL;
	}
	topic_obj = mros_topic_connector_get_topic_obj(mgrp, topic_id);
	if (topic_obj == MROS_COBJ_NULL) {
		return MROS_FALSE;
	}
	obj = mros_topic_connector_get_first(mgrp, topic_obj);
	while (obj != MROS_COBJ_NULL) {
		(void)mros_topic_connector_get(obj, &connector);
		mRosNodeEnumType type = mros_node_type(connector.node_id);
		if (type == ROS_NODE_TYPE_INNER) {
			return MROS_TRUE;
		}
		obj = mros_topic_connector_get_next(mgrp, topic_obj, obj);
	}
	return MROS_FALSE;
}


static mRosReturnType mros_proc_slave_request_topic(mRosCommTcpClientType *client, mRosPacketType *packet)
{
	mRosReturnType ret;
	mRosTopicIdType topic_id;
	mRosSizeType res;

	ret = mros_packet_get_topic_name(packet, topic_name_buffer, MROS_TOPIC_NAME_MAXLEN);
	if (ret != MROS_E_OK) {
		return ret;
	}
	ret = mros_topic_get(topic_name_buffer, &topic_id);
	if (ret != MROS_E_OK) {
		return ret;
	}
	mros_boolean is_exist = mros_publisher_is_exist(topic_id);
	if (is_exist == MROS_FALSE) {
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

mRosReturnType mros_proc_pub(mRosPacketType *packet)
{
	return MROS_E_OK;
}
