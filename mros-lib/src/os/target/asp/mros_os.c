#include "mros_os_target.h"
#include "mros_protocol_master_cimpl.h"
#include "mros_protocol_slave_cimpl.h"
#include "mros_protocol_subscribe_cimpl.h"
#include "mros_protocol_publish_cimpl.h"
#include "mros_os_config.h"
#include "mros_comm_cimpl.h"
#include "mros_comm_tcp_client_factory_cimpl.h"
#include "mros_exclusive_area.h"
#include "mros_node_cimpl.h"
#include "mros_packet_decoder_cimpl.h"
#include "mros_packet_encoder_cimpl.h"
#include "mros_protocol_server_proc_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_topic_data_publisher_cimpl.h"
#include "mros_topic_data_subscriber_cimpl.h"

#include "kernel_cfg.h"

mRosTaskIdType mros_get_taskid(void)
{
	mRosTaskIdType tid;
	(void)get_tid(&tid);
	return tid;
}

mRosTaskPriorityType mros_get_taskpri(void)
{
	mRosTaskIdType tid;
	PRI pri;
	(void)get_tid(&tid);
	(void)get_pri(tid, &pri);
	return pri;
}

void mros_change_taskpri(mRosTaskPriorityType priority)
{
	mRosTaskIdType tid;
	(void)get_tid(&tid);
	 chg_pri(tid, priority);
	 return;
}

void mros_sleep_task(void)
{
	(void)slp_tsk();
}

void mros_wakeup_task(mRosTaskIdType task_id)
{
	(void)wup_tsk(task_id);
}

static void do_packet_encoder_test(void);

void main_task()
{
	mRosReturnType ret;
	syslog(LOG_NOTICE, "**********mROS main task start**********");
	mros_comm_init();
	mros_exclusive_area_init();

	ret = mros_comm_tcp_client_factory_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_comm_tcp_client_factory_init()=%d", ret);
		return;
	}
	ret = mros_node_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_node_init()=%d", ret);
		return;
	}
	ret = mros_topic_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_topic_init()=%d", ret);
		return;
	}
	ret = mros_packet_decoder_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_packet_decoder_init()=%d", ret);
		return;
	}
	ret = mros_packet_encoder_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_packet_encoder_init()=%d", ret);
		return;
	}
	ret = mros_proc_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_proc_init()=%d", ret);
		return;
	}
	ret = mros_topic_data_publisher_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_topic_data_publisher_init()=%d", ret);
		return;
	}
	ret = mros_topic_data_subscriber_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_topic_data_subscriber_init()=%d", ret);
		return;
	}
#if 0
	ret = mros_protocol_subscribe_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_protocol_subscribe_init()=%d", ret);
		return;
	}
	ret = mros_protocol_publish_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_protocol_publish_init()=%d", ret);
		return;
	}
	ret = mros_protocol_slave_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_protocol_slave_init()=%d", ret);
		return;
	}
	ret = mros_protocol_master_init();
	if (ret != MROS_E_OK) {
		syslog(LOG_ERROR, "mros_protocol_master_init()=%d", ret);
		return;
	}


	act_tsk(PUB_TASK);
	act_tsk(SUB_TASK);
	act_tsk(XML_SLV_TASK);
	act_tsk(XML_MAS_TASK);

#else
	do_packet_encoder_test();
#endif
	syslog(LOG_NOTICE,"**********mROS Main task finish**********");
	return;
}

void sub_task()
{
	syslog(LOG_NOTICE, "**********mROS sub task start**********");
	mros_protocol_subscribe_run();
	return;
}

void pub_task()
{
	syslog(LOG_NOTICE, "**********mROS pub task start**********");
	mros_protocol_publish_run();
	return;
}

void xml_slv_task()
{
	syslog(LOG_NOTICE, "**********mROS slv task start**********");
	mros_protocol_slave_run();
	return;
}

void xml_mas_task()
{
	syslog(LOG_NOTICE, "**********mROS mas task start**********");
	mros_protocol_master_run();
	return;
}

void cyclic_handler(intptr_t exinf)
{
	//iwup_tsk(SUB_TASK);
	//iwup_tsk(XML_SLV_TASK);
	return;
}
#include "mros_protocol_client_rpc_cimpl.h"

static void do_packet_encoder_test(void)
{
	mRosEncodeArgType arg;
	mRosPacketType packet;
	mRosReturnType ret;
	static char buffer[512];
	mRosCommTcpClientType client;
	mRosSizeType rlen;

	ret = mros_comm_tcp_client_init(&client, MROS_MASTER_IPADDR, MROS_MASTER_PORT_NO);
	if (ret != MROS_E_OK) {
		syslog(LOG_NOTICE, "mros_comm_tcp_client_init()=%d", ret);
		return;
	}
	packet.data = buffer;
	packet.total_size = sizeof(buffer);
	packet.data_size = 0;

	ret = mros_comm_tcp_client_connect(&client);
	if (ret != MROS_E_OK) {
		syslog(LOG_NOTICE, "mros_comm_tcp_client_connect()=%d", ret);
		return;
	}
	mRosRegisterTopicReqType req;
	mRosRegisterTopicResType res;
	req.node_name = "node1";
	req.req_packet = &packet;
	req.topic_name = "topic_name1";
	req.topic_typename = "std_msgs/String";
	res.reply_packet = &packet;

	ret = mros_rpc_register_publisher(&client, &req, &res);
	if (ret != MROS_E_OK) {
		syslog(LOG_NOTICE, "mros_rpc_register_publisher()=%d", ret);
		return;
	}
	syslog(LOG_NOTICE, "data_size=%d", packet.data_size);
	syslog(LOG_NOTICE, "packet=%s", packet.data);

	return;
}
