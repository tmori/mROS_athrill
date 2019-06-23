#include "ros.h"
#include "mros_node_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"

using namespace ros;


void init(int argc, char *argv, std::string& node_name)
{
	mRosNodeIdType id;
	mRosReturnType ret = mros_node_create_inner(node_name.c_str(), &id);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return;
	}
	return;
}

Subscriber NodeHandle::subscriber(std::string& topic, int queue_size, void(*fp)(std::string*))
{
	Subscriber sub;
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;

	ret = mros_node_get_bytid(&connector.node_id);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return sub;
	}

	ret = mros_topic_create(topic.c_str(), &connector.topic_id);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return sub;
	}

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_SUB);
	if (mgrp == NULL) {
		//TODO ERROR LOG
		return sub;
	}
	connector.func_id = (mRosFuncIdType)fp;

	ret = mros_topic_connector_add(mgrp, &connector);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return sub;
	}

	//TODO ROSマスタへ登録する
	return sub;
}

Publisher NodeHandle::advertise(std::string& topic, int queue_size)
{
	Publisher pub;
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;

	ret = mros_node_get_bytid(&connector.node_id);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return pub;
	}

	ret = mros_topic_create(topic.c_str(), &connector.topic_id);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return pub;
	}

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_PUB);
	if (mgrp == NULL) {
		//TODO ERROR LOG
		return pub;
	}
	connector.func_id = (mRosFuncIdType)MROS_ID_NONE;

	ret = mros_topic_connector_add(mgrp, &connector);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return pub;
	}

	//TODO ROSマスタへ登録する
	return pub;
}


void Publisher::publish(std_msgs::String& data)
{
	//TODO
	return;
}
