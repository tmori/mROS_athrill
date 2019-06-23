#include "mros_protocol_master_cimpl.h"
#include "mros_packet_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"
#include "mros_config.h"
#include "mros_exclusive_area.h"
#include "mros_wait_queue.h"
#include <stdlib.h>

typedef struct {
	mRosProtocolMasterStateEnumType 	state;
	mRosEncodeArgType 					arg;
	mRosPacketType						packet;
} mRosProtocolMasterType;

static mRosProtocolMasterType mros_protocol_master;
static mRosReturnType mros_protocol_master_register_publisher(mRosProtocolMasterRequestType *pub_req);
static mRosReturnType mros_protocol_master_register_subscriber(mRosProtocolMasterRequestType *sub_req);

mRosReturnType mros_protocol_master_init(void)
{
	//TODO open sever port
	//TODO open slave port
	//TODO open pub port

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

static mRosReturnType mros_protocol_master_register(mRosProtocolMasterRequestType *req, mRosTopicConnectorEnumType type)
{
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp = mros_topic_connector_factory_get(type);
	const char* method;

	if (type == MROS_TOPIC_CONNECTOR_PUB) {
		method = "registerPublisher";
	}
	else {
		method = "registerSubscriber";
	}

	if (mgrp == NULL) {
		return MROS_E_INVAL;
	}
	ret = mros_topic_connector_get(req->connector_obj,  &connector);
	if (ret != MROS_E_OK) {
		return MROS_E_INVAL;
	}

	mros_protocol_master.arg.args_int = 1;
	mros_protocol_master.arg.argi[0] = connector.node_id;

	mros_protocol_master.arg.args_char = 4;
	mros_protocol_master.arg.argv[0] = method;
	mros_protocol_master.arg.argv[1] = mros_topic_get_topic_name(connector.topic_id);
	mros_protocol_master.arg.argv[2] = mros_topic_get_topic_typename(connector.topic_id);
	mros_protocol_master.arg.argv[3] = MROS_URI_SLAVE;

	ret = mros_packet_encode(&mros_protocol_master.arg, &mros_protocol_master.packet);
	if (ret != MROS_E_OK) {
		return ret;
	}
	//TODO sendReply
	//TODO master task から通信しないといけないかどうか要調査

	return ret;
}

static mRosReturnType mros_protocol_master_request_topic(mRosProtocolMasterRequestType *req)
{
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_SUB);
	if (mgrp == NULL) {
		return MROS_E_INVAL;
	}
	ret = mros_topic_connector_get(req->connector_obj,  &connector);
	if (ret != MROS_E_OK) {
		return MROS_E_INVAL;
	}

	mros_protocol_master.arg.args_int = 1;
	mros_protocol_master.arg.argi[0] = connector.node_id;

	mros_protocol_master.arg.args_char = 2;
	mros_protocol_master.arg.argv[0] = "requestTopic";
	mros_protocol_master.arg.argv[1] = mros_topic_get_topic_name(connector.topic_id);
	mros_protocol_master.arg.argv[2] = "TCPROS";

	ret = mros_packet_encode(&mros_protocol_master.arg, &mros_protocol_master.packet);
	if (ret != MROS_E_OK) {
		return ret;
	}
	//TODO sendReply
	//TODO master task から通信しないといけないかどうか要調査

	return ret;
}

static mRosReturnType mros_protocol_master_register_publisher(mRosProtocolMasterRequestType *pub_req)
{
	mRosReturnType ret;

	mros_protocol_master.state = MROS_PROTOCOL_MASTER_STATE_REGISTER_PUBLISHER;

	//TODO ROSマスタと接続
	ret = mros_protocol_master_register(pub_req, MROS_TOPIC_CONNECTOR_PUB);
	//TODO ROSマスタと切断

	mros_protocol_master.state = MROS_PROTOCOL_MASTER_STATE_WAITING;

	return ret;
}


static mRosReturnType mros_protocol_master_register_subscriber(mRosProtocolMasterRequestType *sub_req)
{
	mRosReturnType ret;

	mros_protocol_master.state = MROS_PROTOCOL_MASTER_STATE_REGISTER_SUBSCRIBER;

	//TODO ROSマスタと接続
	ret = mros_protocol_master_register(sub_req, MROS_TOPIC_CONNECTOR_SUB);
	if (ret != MROS_E_OK) {
		return ret;
	}
	//TODO 出版ノードが複数いる場合の考慮が必要
	//TODO ROSマスタと切断

	mros_protocol_master.state = MROS_PROTOCOL_MASTER_STATE_REQUESTING_TOPIC;
	//TODO SLAVEと接続

	ret = mros_protocol_master_request_topic(sub_req);
	if (ret != MROS_E_OK) {
		return ret;
	}
	//TODO SLAVEと切断
	//TODO ROSマスタと切断

	mros_protocol_master.state = MROS_PROTOCOL_MASTER_STATE_WAITING;

	return ret;
}
