#include "mros_protocol_subscribe_cimpl.h"
#include "mros_types.h"
#include "mros_config.h"
#include "mros_exclusive_area.h"
#include "mros_wait_queue.h"
#include "mros_comm_tcp_client_factory_cimpl.h"
#include "mros_packet_decoder_cimpl.h"
#include "mros_node_cimpl.h"
#include "mros_memory.h"
#include "mros_packet_encoder_cimpl.h"
#include "mros_protocol_client_rpc_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_node_cimpl.h"
#include "mros_topic_runner_cimpl.h"
#include <stdlib.h>

typedef union {
	char buffer;
	char buffer1[MROS_PACKET_MAXSIZE_REQ_TCPROS];
	char buffer2[MROS_PACKET_MAXSIZE_RES_TCPROS];
} mRosSubscribePacketTcpRosBufferType;


typedef struct {
	mRosProtocolSubscribeStateEnumType 	state;
	mRosEncodeArgType 					arg;
	mRosPacketType						tcpros_packet;
	mRosTopicConnectorManagerType 		*pub_mgrp;// for outer
} mRosProtocolSubscribeType;

static mRosProtocolSubscribeType mros_protocol_subscribe;
static mRosSubscribePacketTcpRosBufferType mros_subscribe_packet_tcpros_buffer;


/*******************************************************
 * START: Publish Config
 *******************************************************/
//TODO 要検討
//本メモリプールは，コネクションごとに作成する必要がある
//コネクションと本メモリプールをどうやって結び付けるかは要検討
//おそらく想定するデータ型と想定コネクション数から本コンフィグを自動生成すべきと考える．

#define ROS_OUTER_TOPIC_PUBLISHER_CONFIG_NUM			3U
#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL1_SIZE		4U
#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL1_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_outer_topic_publisher_mempool1, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL1_QUELEN, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL1_SIZE);

#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL2_SIZE		8U
#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL2_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_outer_topic_publisher_mempool2, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL2_QUELEN, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL2_SIZE);

#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL3_SIZE		16U
#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL3_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_outer_topic_publisher_mempool3, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL3_QUELEN, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL3_SIZE);

static mRosMemoryConfigType *ros_outer_topic_publisher_config[ROS_OUTER_TOPIC_PUBLISHER_CONFIG_NUM] = {
		&ros_outer_topic_publisher_mempool1_config,
		&ros_outer_topic_publisher_mempool2_config,
		&ros_outer_topic_publisher_mempool3_config,
};
MROS_MEMORY_CONFIG_DECLARE_MANAGER(ros_outer_topic_publisher_mempool, ROS_OUTER_TOPIC_PUBLISHER_CONFIG_NUM);
/*******************************************************
 * END
 *******************************************************/

mRosReturnType mros_protocol_subscribe_init(void)
{
	mRosReturnType ret;
	mros_protocol_subscribe.tcpros_packet.total_size = sizeof(mRosSubscribePacketTcpRosBufferType);
	mros_protocol_subscribe.tcpros_packet.data = &mros_subscribe_packet_tcpros_buffer.buffer;
	mros_protocol_subscribe.state = MROS_PROTOCOL_SUBSCRIBE_STATE_WAITING;
	mros_protocol_subscribe.pub_mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_PUB);
	ret = mros_mem_init(ROS_OUTER_TOPIC_PUBLISHER_CONFIG_NUM, ros_outer_topic_publisher_config, &ros_outer_topic_publisher_mempool);
	return ret;
}

void mros_protocol_subscribe_run(void)
{
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosCommTcpClientListReqEntryType *client_req;
	mRosContainerObjType cobj;
	mRosRcpRosReqType req;
	mRosTcpRosResType res;
	mROsExclusiveUnlockObjType unlck_obj;

	req.req_packet = &mros_protocol_subscribe.tcpros_packet;
	res.reply_packet = &mros_protocol_subscribe.tcpros_packet;

	mros_exclusive_lock(&mros_exclusive_area, &unlck_obj);
	while (MROS_TRUE) {
		mRosWaitListEntryType *wait_entry = mros_server_queue_wait(&mros_subscribe_wait_queue);
		if (wait_entry == NULL) {
			mros_topic_data_subscriber_run();
			continue;
		}
		client_req = (mRosCommTcpClientListReqEntryType*)wait_entry->data.reqp;
		connector.topic_id = client_req->data.reqobj.topic_id;
		connector.func_id = (mRosFuncIdType)MROS_ID_NONE;
		ret = mros_node_create_outer(&connector.node_id);
		if (ret != MROS_E_OK) {
			//TODO ERR LOG
			continue;
		}
		ret = mros_topic_connector_add(mros_protocol_subscribe.pub_mgrp, &connector, MROS_OUTER_CONNECTOR_QUEUE_MAXLEN, &ros_outer_topic_publisher_mempool);
		if (ret != MROS_E_OK) {
			//TODO ERR LOG
			continue;
		}

		ret = mros_comm_tcp_client_ip32_init(&client_req->data.client, client_req->data.reqobj.ipaddr, client_req->data.reqobj.port);
		if (ret != MROS_E_OK) {
			//TODO ERR LOG
			continue;
		}
		ret = mros_comm_tcp_client_connect(&client_req->data.client);
		if (ret != MROS_E_OK) {
			//TODO ERR LOG
			continue;
		}

		req.node_name = mros_node_name(connector.node_id);
		req.topic_name = mros_topic_get_topic_name(connector.topic_id);
		req.topic_typename = mros_topic_get_topic_typename(connector.topic_id);
		ret = mros_rpc_tcpros(&client_req->data.client, &req, &res);
		if (ret != MROS_E_OK) {
			//TODO ERR LOG
			continue;
		}

		cobj = mros_topic_connector_get_obj(mros_protocol_subscribe.pub_mgrp, &connector);
		ret = mros_topic_connector_set_connection(cobj, client_req);
		if (ret != MROS_E_OK) {
			//TODO ERR LOG
			continue;
		}
	}
	mros_exclusive_unlock(&unlck_obj);
	return;
}
