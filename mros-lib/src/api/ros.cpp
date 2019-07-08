#include "ros.h"
#include "mros_node_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"
#include "mros_exclusive_area.h"
#include "mros_wait_queue.h"
#include "mros_protocol_master_cimpl.h"
#include "mros_usr_config.h"
#include <string.h>


void ros::init(int argc, char *argv, std::string node_name)
{
	mRosNodeIdType id;
	mRosReturnType ret;
	mROsExclusiveUnlockObjType unlck_obj;

	mros_exclusive_lock(&mros_exclusive_area, &unlck_obj);
	ret = mros_node_create_inner(node_name.c_str(), &id);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
	}
	mros_exclusive_unlock(&unlck_obj);
	return;
}

ros::Subscriber ros::NodeHandle::subscriber(std::string topic, int queue_size, void(*fp)(std::string*))
{
	Subscriber sub;
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;
	mRosProtocolMasterRequestType req;
	mRosWaitListEntryType client_wait;
	mROsExclusiveUnlockObjType unlck_obj;

	mros_client_wait_entry_init(&client_wait, &req);

	mros_exclusive_lock(&mros_exclusive_area, &unlck_obj);

	sub.set(MROS_COBJ_NULL);

	ret = mros_node_get_bytid(&connector.node_id);
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return sub;
	}

	ret = mros_topic_create(topic.c_str(), "std_msgs/String", &connector.topic_id);//TODO typename
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return sub;
	}

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_SUB);
	if (mgrp == MROS_NULL) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return sub;
	}
	connector.func_id = (mRosFuncIdType)fp;

	ret = mros_topic_connector_add(mgrp, &connector, queue_size, MROS_NULL);
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return sub;
	}
	mRosContainerObjType obj = mros_topic_connector_get_obj(mgrp, &connector);
	if (obj == MROS_COBJ_NULL) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return sub;
	}
	sub.set(obj);

	//ROSマスタへ登録する
	req.req_type = MROS_PROTOCOL_MASTER_REQ_REGISTER_SUBSCRIBER;
	req.connector_obj = obj;

	mros_client_wait_for_request_done(&mros_master_wait_queue, &client_wait);
	mros_exclusive_unlock(&unlck_obj);
	return sub;
}

ros::Publisher ros::NodeHandle::advertise(std::string topic, int queue_size)
{
	Publisher pub;
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;
	mRosProtocolMasterRequestType req;
	mRosWaitListEntryType client_wait;
	mROsExclusiveUnlockObjType unlck_obj;

	mros_client_wait_entry_init(&client_wait, &req);

	mros_exclusive_lock(&mros_exclusive_area, &unlck_obj);
	pub.set(MROS_COBJ_NULL);

	ret = mros_node_get_bytid(&connector.node_id);
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return pub;
	}

	ret = mros_topic_create(topic.c_str(), "std_msgs/String", &connector.topic_id);//TODO typename
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return pub;
	}

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_PUB);
	if (mgrp == MROS_NULL) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return pub;
	}
	connector.func_id = (mRosFuncIdType)MROS_ID_NONE;

	ret = mros_topic_connector_add(mgrp, &connector, queue_size, &ros_inner_topic_publisher_mempool);
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return pub;
	}
	mRosContainerObjType obj = mros_topic_connector_get_obj(mgrp, &connector);
	if (obj == MROS_COBJ_NULL) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return pub;
	}

	pub.set(obj);

	//ROSマスタへ登録する
	req.req_type = MROS_PROTOCOL_MASTER_REQ_REGISTER_PUBLISHER;
	req.connector_obj = obj;

	mros_client_wait_for_request_done(&mros_master_wait_queue, &client_wait);
	mros_exclusive_unlock(&unlck_obj);
	return pub;
}


void ros::Publisher::publish(std_msgs::String& data)
{
	mRosReturnType ret;
	const char *snd_data = data.data.c_str();
	mRosSizeType len = strlen(snd_data);
	mROsExclusiveUnlockObjType unlck_obj;

	mros_exclusive_lock(&mros_exclusive_area, &unlck_obj);
	ret = mros_topic_connector_put_data((mRosContainerObjType)this->get(), snd_data, len);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
	}
	mros_exclusive_unlock(&unlck_obj);
	return;
}


void ros::Rate::sleep(void)
{
	mros_sleep_task_msec(ROS_RATE_RATE_SEC_UNIT/this->rate);
	return;
}

void ros::spin(void){
	slp_tsk();
	return;
}
