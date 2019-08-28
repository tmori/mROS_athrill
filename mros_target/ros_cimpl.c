#include "ros_cimpl.h"
#include "mros_node_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"
#include "mros_exclusive_area.h"
#include "mros_wait_queue.h"
#include "mros_protocol_master_cimpl.h"
#include "mros_protocol_operation_cimpl.h"
#include "mros_usr_config.h"
#include "mros_topic_callback.h"
#include <string.h>

static int mros_id = 0;

void ros_init(mRosObjType *cobj, int argc, char *argv, const char* node_name)
{
	mRosNodeIdType id;
	mRosReturnType ret;
	mROsExclusiveUnlockObjType unlck_obj;

	mros_exclusive_lock(&mros_exclusive_area, &unlck_obj);
	mros_id++;
	ret = mros_node_create_inner(node_name, &id);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
	}
	cobj->id = mros_id;
	mros_exclusive_unlock(&unlck_obj);
	return;
}

int ros_subscribe(mRosObjType *cobj, const char* topic, int queue_size, void (*fp) (char *))
{
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;
	mRosProtocolMasterRequestType req;
	mRosWaitListEntryType client_wait;
	mROsExclusiveUnlockObjType unlck_obj;
	mros_uint32 type_id;

	mros_client_wait_entry_init(&client_wait, &req);

	mros_exclusive_lock(&mros_exclusive_area, &unlck_obj);

	ret = mros_node_get_bytid(&connector.node_id);
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return -1;
	}

	ret = mros_topic_create(topic, "std_msgs/String", &connector.topic_id);
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return -1;
	}
	(void)mros_topic_set_typeid(connector.topic_id, 0);
	(void)mros_topic_set_definition(connector.topic_id, NULL);
	(void)mros_topic_get_typeid(connector.topic_id, &type_id);
	(void)mros_topic_set_md5sum(connector.topic_id, "992ce8a1687cec8c8bd883ec73ca41d1");

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_SUB);
	if (mgrp == MROS_NULL) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return -1;
	}
	connector.func_id = (mRosFuncIdType)fp;

	ret = mros_topic_connector_add(mgrp, &connector, queue_size, MROS_NULL);
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return -1;
	}
	mRosContainerObjType obj = mros_topic_connector_get_obj(mgrp, &connector);
	if (obj == MROS_COBJ_NULL) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return -1;
	}
	cobj->objp = (void*)obj;

	//ROSマスタへ登録する
	req.req_type = MROS_PROTOCOL_MASTER_REQ_REGISTER_SUBSCRIBER;
	req.connector_obj = obj;

	mros_client_wait_for_request_done(&mros_master_wait_queue, &client_wait);
	mros_exclusive_unlock(&unlck_obj);
	return 0;
}

int ros_advertise(mRosObjType *cobj, const char* topic, int queue_size)
{
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;
	mRosProtocolMasterRequestType req;
	mRosWaitListEntryType client_wait;
	mROsExclusiveUnlockObjType unlck_obj;
	mros_uint32 type_id;

	mros_client_wait_entry_init(&client_wait, &req);

	mros_exclusive_lock(&mros_exclusive_area, &unlck_obj);

	ret = mros_node_get_bytid(&connector.node_id);
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return -1;
	}

	ret = mros_topic_create(topic, "std_msgs/String", &connector.topic_id);
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return -1;
	}
	(void)mros_topic_set_typeid(connector.topic_id, 0);
	(void)mros_topic_set_definition(connector.topic_id, NULL);
	(void)mros_topic_get_typeid(connector.topic_id, &type_id);
	(void)mros_topic_set_md5sum(connector.topic_id, "992ce8a1687cec8c8bd883ec73ca41d1");

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_PUB);
	if (mgrp == MROS_NULL) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return -1;
	}
	connector.func_id = (mRosFuncIdType)MROS_ID_NONE;

	ret = mros_topic_connector_add(mgrp, &connector, queue_size, &ros_inner_topic_publisher_mempool);
	if (ret != MROS_E_OK) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return -1;
	}
	mRosContainerObjType obj = mros_topic_connector_get_obj(mgrp, &connector);
	if (obj == MROS_COBJ_NULL) {
		mros_exclusive_unlock(&unlck_obj);
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return -1;
	}

	cobj->objp = (void*)obj;

	//ROSマスタへ登録する
	req.req_type = MROS_PROTOCOL_MASTER_REQ_REGISTER_PUBLISHER;
	req.connector_obj = obj;

	mros_client_wait_for_request_done(&mros_master_wait_queue, &client_wait);
	mros_exclusive_unlock(&unlck_obj);
	return 0;
}


int ros_publish(mRosObjType* cobj, void *data, int datalen)
{
	mRosReturnType ret;
	char *snd_data;
	char *bodyp;
	mRosSizeType size;
	mROsExclusiveUnlockObjType unlck_obj;

	size = mros_protocol_get_buffersize(datalen);

	mros_exclusive_lock(&mros_exclusive_area, &unlck_obj);
	ret = mros_topic_connector_alloc_data((mRosContainerObjType)cobj->objp, &snd_data, size);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
	}
	bodyp = mros_protocol_get_body(snd_data);
    size = datalen + 4;
    memcpy(bodyp, &size, 4);
    bodyp += 4;
	memcpy(bodyp, data, datalen);
	mros_exclusive_unlock(&unlck_obj);
	return 0;
}


void mros_topic_callback(mros_uint32 type_id, mRosFuncIdType func_id, const char *data)
{
	void (*fp)(void *ptr);
	fp = (void (*)(void *))func_id;

	fp((char*)data);
	return;
}

