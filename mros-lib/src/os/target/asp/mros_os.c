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
#include "mros_topic_connector_factory_cimpl.h"
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
	return;
}

void mros_sleep_task_msec(mRosTaskSleepIntervalType msec)
{
	(void)dly_tsk(msec);
	return;
}

void mros_wakeup_task(mRosTaskIdType task_id)
{
	(void)wup_tsk(task_id);
	return;
}

void main_task()
{
	mRosReturnType ret;
	ROS_INFO("**********mROS main task start**********");
	mros_comm_init();
	mros_exclusive_area_init(XML_MAS_TASK, SUB_TASK);

	ret = mros_comm_tcp_client_factory_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	ret = mros_node_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	ret = mros_topic_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	mRosTopicConnectorManagerType *mgrp = mros_topic_connector_factory_create(MROS_TOPIC_CONNECTOR_PUB);
	if (mgrp == MROS_NULL) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, MROS_E_INVAL);
		return;
	}
	mgrp = mros_topic_connector_factory_create(MROS_TOPIC_CONNECTOR_SUB);
	if (mgrp == MROS_NULL) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, MROS_E_INVAL);
		return;
	}
	ret = mros_packet_decoder_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	ret = mros_packet_encoder_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	ret = mros_proc_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	ret = mros_topic_data_publisher_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	ret = mros_topic_data_subscriber_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}

	ret = mros_protocol_subscribe_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	ret = mros_protocol_publish_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	ret = mros_protocol_slave_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	ret = mros_protocol_master_init();
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}

	act_tsk(PUB_TASK);
	act_tsk(SUB_TASK);
	act_tsk(XML_SLV_TASK);
	act_tsk(XML_MAS_TASK);
	act_tsk(USR_TASK1);
	act_tsk(USR_TASK2);

	ROS_INFO("**********mROS Main task finish**********");
	return;
}

void sub_task()
{
	ROS_INFO("**********mROS sub task start**********");
	mros_protocol_subscribe_run();
	return;
}

void pub_task()
{
	ROS_INFO("**********mROS pub task start**********");
	mros_protocol_publish_run();
	return;
}

void xml_slv_task()
{
	ROS_INFO("**********mROS slv task start**********");
	mros_protocol_slave_run();
	return;
}

void xml_mas_task()
{
	ROS_INFO("**********mROS mas task start**********");
	mros_protocol_master_run();
	return;
}

void cyclic_handler(intptr_t exinf)
{
	iwup_tsk(SUB_TASK);
	return;
}
