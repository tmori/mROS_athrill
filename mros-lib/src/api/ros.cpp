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
#define ROS_TOPIC_PUBLISHER_MEMPOOL1_SIZE		16U
#define ROS_TOPIC_PUBLISHER_MEMPOOL1_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_topic_publisher_mempool1, ROS_TOPIC_PUBLISHER_MEMPOOL1_QUELEN, ROS_TOPIC_PUBLISHER_MEMPOOL1_SIZE);

#define ROS_TOPIC_PUBLISHER_MEMPOOL2_SIZE		32U
#define ROS_TOPIC_PUBLISHER_MEMPOOL2_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_topic_publisher_mempool2, ROS_TOPIC_PUBLISHER_MEMPOOL2_QUELEN, ROS_TOPIC_PUBLISHER_MEMPOOL2_SIZE);

#define ROS_TOPIC_PUBLISHER_MEMPOOL3_SIZE		64U
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
	mRosReturnType ret;
	mROsExclusiveUnlockObjType unlck_obj;

	mros_exclusive_lock(&mros_exclusive_area, &unlck_obj);
	ret = mros_node_create_inner(node_name.c_str(), &id);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
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
		mros_exclusive_unlock(&unlck_obj);
		return sub;
	}

	ret = mros_topic_create(topic.c_str(), "std_msgs/String", &connector.topic_id);//TODO typename
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		mros_exclusive_unlock(&unlck_obj);
		return sub;
	}

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_SUB);
	if (mgrp == MROS_NULL) {
		//TODO ERROR LOG
		mros_exclusive_unlock(&unlck_obj);
		return sub;
	}
	connector.func_id = (mRosFuncIdType)fp;

	ret = mros_topic_connector_add(mgrp, &connector, queue_size, MROS_NULL);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		mros_exclusive_unlock(&unlck_obj);
		return sub;
	}
	mRosContainerObjType obj = mros_topic_connector_get_obj(mgrp, &connector);
	if (obj == MROS_COBJ_NULL) {
		//TODO ERRLOG
		mros_exclusive_unlock(&unlck_obj);
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
		//TODO ERROR LOG
		mros_exclusive_unlock(&unlck_obj);
		return pub;
	}

	ret = mros_topic_create(topic.c_str(), "std_msgs/String", &connector.topic_id);//TODO typename
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		mros_exclusive_unlock(&unlck_obj);
		return pub;
	}

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_PUB);
	if (mgrp == MROS_NULL) {
		//TODO ERROR LOG
		mros_exclusive_unlock(&unlck_obj);
		return pub;
	}
	connector.func_id = (mRosFuncIdType)MROS_ID_NONE;

	//TODO 初期化場所はここではない．
	ret = mros_mem_init(ROS_TOPIC_PUBLISHER_CONFIG_NUM, ros_topic_publisher_config, &ros_topic_publisher_mempool);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		mros_exclusive_unlock(&unlck_obj);
		return pub;
	}

	ret = mros_topic_connector_add(mgrp, &connector, queue_size, &ros_topic_publisher_mempool);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		mros_exclusive_unlock(&unlck_obj);
		return pub;
	}
	mRosContainerObjType obj = mros_topic_connector_get_obj(mgrp, &connector);
	if (obj == MROS_COBJ_NULL) {
		//TODO ERROR LOG
		mros_exclusive_unlock(&unlck_obj);
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
		//TODO ERROR LOG
	}
	mros_exclusive_unlock(&unlck_obj);
	return;
}

//TODO callback
void mros_topic_callback(mRosFuncIdType func_id, const char *data)
{
	void (*fp)(std::string *ptr);
	fp = (void (*)(std::string *))func_id;
	std::string msg((const char*)data);
	fp(&msg);
	return;
}
