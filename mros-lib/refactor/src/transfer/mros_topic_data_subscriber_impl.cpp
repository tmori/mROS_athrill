#include "mros_topic_data_subscriber.h"
#include "mros_topic_connector.h"
#include "mros_node.h"

using namespace mros::transfer;
using namespace mros::topic;
using namespace mros::topic::topology;
using namespace mros::memory;
using namespace mros::node;


static PrimitiveContainer<RosTopicConnectorIdType> *connector_container;
static PrimitiveContainer<RosTopicIdType> 			*topic_container;

mRosReturnType RosTopicDataSubscriber::init(void)
{
	topic_container = new PrimitiveContainer<RosTopicIdType>(10); //TODO;
	connector_container = new PrimitiveContainer<RosTopicConnectorIdType>(10); //TODO;

	return MROS_E_OK;
}


static void ros_topic_subscribe(RosTopicIdType topic_id)
{
	mRosReturnType ret;
	RosTopicConnectorType connector;
	mRosMemoryListEntryType *topic_data;

	ret = RosTopicConnector::get_sub_connectors(topic_id, *connector_container);
	if (ret != MROS_E_OK) {
		return;
	}

	ret = RosTopic::get_data(topic_id, &topic_data);
	if (ret != MROS_E_OK) {
		(void)RosTopicConnector::rel_sub_connectors(*connector_container);
		return;
	}

	for (mros_uint32 i = 0; i < connector_container->size(); i++) {
		ret = RosTopicConnector::get_sub(connector_container->get(i), connector);
		if (ret != MROS_E_OK) {
			//TOODO ERROR LOG
			continue;
		}

		ret = RosNode::put_sub_topic(connector.node_id, *topic_data, connector.func_id);
		if (ret != MROS_E_OK) {
			//TOODO ERROR LOG
			continue;
		}
	}

	(void)RosTopicConnector::rel_sub_connectors(*connector_container);
	//TODO free topic_data
	return;
}

void RosTopicDataSubscriber::subscribe(void)
{
	mRosReturnType ret;

	ret = RosTopicConnector::get_sub_topics(*topic_container);
	if (ret != MROS_E_OK) {
		return;
	}
	for (mros_uint32 i = 0; i < topic_container->size(); i++) {
		ros_topic_subscribe(topic_container->get(i));
	}

	return;
}

RosTopicDataSubscriber::RosTopicDataSubscriber()
{
	//TODO
}

RosTopicDataSubscriber::~RosTopicDataSubscriber()
{
	//TODO
}
