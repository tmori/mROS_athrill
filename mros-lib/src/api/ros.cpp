#include "ros.h"
#include "mros_node_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"
#include "mros_exclusive_area.h"
#include "mros_wait_queue.h"
#include "mros_protocol_master_cimpl.h"
#include <string.h>


/*******************************************************
 * START: Publish Config
 *******************************************************/
//TODO 要検討
//本メモリプールは，コネクションごとに作成する必要がある
//コネクションと本メモリプールをどうやって結び付けるかは要検討
//おそらく想定するデータ型と想定コネクション数から本コンフィグを自動生成すべきと考える．

#define ROS_TOPIC_PUBLISHER_CONFIG_NUM			3U
#define ROS_TOPIC_PUBLISHER_MEMPOOL1_SIZE		4U
#define ROS_TOPIC_PUBLISHER_MEMPOOL1_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_topic_publisher_mempool1, ROS_TOPIC_PUBLISHER_MEMPOOL1_QUELEN, ROS_TOPIC_PUBLISHER_MEMPOOL1_SIZE);

#define ROS_TOPIC_PUBLISHER_MEMPOOL2_SIZE		8U
#define ROS_TOPIC_PUBLISHER_MEMPOOL2_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_topic_publisher_mempool2, ROS_TOPIC_PUBLISHER_MEMPOOL2_QUELEN, ROS_TOPIC_PUBLISHER_MEMPOOL2_SIZE);

#define ROS_TOPIC_PUBLISHER_MEMPOOL3_SIZE		16U
#define ROS_TOPIC_PUBLISHER_MEMPOOL3_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_topic_publisher_mempool3, ROS_TOPIC_PUBLISHER_MEMPOOL3_QUELEN, ROS_TOPIC_PUBLISHER_MEMPOOL3_SIZE);

static mRosMemoryConfigType *ros_topic_publisher_config[ROS_TOPIC_PUBLISHER_CONFIG_NUM] = {
		&ros_topic_publisher_mempool1_config,
		&ros_topic_publisher_mempool2_config,
		&ros_topic_publisher_mempool3_config,
};
MROS_MEMORY_CONFIG_DECLARE_MANAGER(ros_topic_publisher_mempool, ROS_TOPIC_PUBLISHER_CONFIG_NUM);
/*******************************************************
 * END
 *******************************************************/


void ros::init(int argc, char *argv, std::string node_name)
{
	mRosNodeIdType id;
	mRosReturnType ret = mros_node_create_inner(node_name.c_str(), &id);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return;
	}
	return;
}

ros::Subscriber ros::NodeHandle::subscriber(std::string topic, int queue_size, void(*fp)(std::string*))
{
	Subscriber sub;
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;

	/*
	 * TODO 要検討
	 *
	 * 本実装では，購読のキュー長は設定しない．
	 * 理由はメモリコピーおよびメモリ使用量を抑止するためである．
	 *
	 * INNERノードであれば，直接コールバック関数を呼び出す方針とし，キューイングしない．
	 * OUTERノードであれば，直接通信APIを呼び出す方針として，キューイングしない．
	 *
	 * 本方針により，subscriberの処理オーバーヘッドが高くなり，非同期通信すべきと
	 * 判断した場合は，上記方針を撤回し，キューイング実装を行うものとする．
	 */

	sub.set(MROS_COBJ_NULL);

	ret = mros_node_get_bytid(&connector.node_id);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return sub;
	}

	ret = mros_topic_create(topic.c_str(), "TODO:typename", &connector.topic_id);//TODO typename
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

	ret = mros_topic_connector_add(mgrp, &connector, queue_size, NULL);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return sub;
	}
	mRosContainerObjType obj = mros_topic_connector_get_obj(mgrp, &connector);
	if (obj == MROS_COBJ_NULL) {
		return sub;
	}
	sub.set(obj);

	{
		//ROSマスタへ登録する
		mRosProtocolMasterRequestType req;
		mRosWaitListEntryType client_wait;

		req.connector_obj = obj;
		req.req_type = MROS_PROTOCOL_MASTER_REQ_REGISTER_SUBSCRIBER;
		mros_client_wait_entry_init(&client_wait, &req);

		mros_exclusive_lock(&mros_master_exclusive_area);
		mros_server_queue_put(&mros_master_wait_queue, &client_wait);
		mros_server_queue_wakeup(&mros_master_wait_queue);
		mros_client_wait(&mros_master_exclusive_area, &client_wait);
		mros_exclusive_unlock(&mros_master_exclusive_area);
	}
	return sub;
}

ros::Publisher ros::NodeHandle::advertise(std::string topic, int queue_size)
{
	Publisher pub;
	mRosReturnType ret;
	mRosTopicConnectorType connector;
	mRosTopicConnectorManagerType *mgrp;

	pub.set(MROS_COBJ_NULL);

	ret = mros_node_get_bytid(&connector.node_id);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return pub;
	}

	ret = mros_topic_create(topic.c_str(), "TODO:typename", &connector.topic_id);//TODO typename
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

	ret = mros_mem_init(ROS_TOPIC_PUBLISHER_CONFIG_NUM, ros_topic_publisher_config, &ros_topic_publisher_mempool);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return pub;
	}

	ret = mros_topic_connector_add(mgrp, &connector, queue_size, &ros_topic_publisher_mempool);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return pub;
	}
	mRosContainerObjType obj = mros_topic_connector_get_obj(mgrp, &connector);
	if (obj == MROS_COBJ_NULL) {
		return pub;
	}

	pub.set(obj);

	{
		//ROSマスタへ登録する
		mRosProtocolMasterRequestType req;
		mRosWaitListEntryType client_wait;

		req.connector_obj = obj;
		req.req_type = MROS_PROTOCOL_MASTER_REQ_REGISTER_PUBLISHER;
		mros_client_wait_entry_init(&client_wait, &req);

		mros_exclusive_lock(&mros_master_exclusive_area);
		mros_server_queue_put(&mros_master_wait_queue, &client_wait);
		mros_server_queue_wakeup(&mros_master_wait_queue);
		mros_client_wait(&mros_master_exclusive_area, &client_wait);
		mros_exclusive_unlock(&mros_master_exclusive_area);
	}
	return pub;
}


void ros::Publisher::publish(std_msgs::String& data)
{
	mRosReturnType ret;
	const char *snd_data = data.data.c_str();
	mRosSizeType len = strlen(snd_data) + 1U;
	ret = mros_topic_connector_put_data((mRosContainerObjType)this->get(), snd_data, len);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return;
	}
	return;
}
