#include "mros_topic_data_publisher.h"
#include "mros_topic_connector.h"
#include "mros_node.h"

using namespace mros::transfer;
using namespace mros::topic;
using namespace mros::topic::topology;
using namespace mros::memory;
using namespace mros::node;

static PrimitiveContainer<RosTopicConnectorIdType> *connector_container;
static PrimitiveContainer<RosTopicIdType> 			*topic_container;

mRosReturnType RosTopicDataPublisher::init(void)
{
	topic_container = new PrimitiveContainer<RosTopicIdType>(10); //TODO;
	connector_container = new PrimitiveContainer<RosTopicConnectorIdType>(10); //TODO;

	return MROS_E_OK;
}

static void ros_topic_publish(RosTopicIdType topic_id)
{
	mRosReturnType ret;
	RosTopicConnectorType connector;
	mRosMemoryListEntryType *topic_data;

	ret = RosTopicConnector::get_pub_connectors(topic_id, *connector_container);
	if (ret != MROS_E_OK) {
		//TODO ERROR LOG
		return;
	}

	for (mros_uint32 i = 0; i < connector_container->size(); i++) {
		ret = RosTopicConnector::get_pub(connector_container->get(i), connector);
		if (ret != MROS_E_OK) {
			//TOODO ERROR LOG
			continue;
		}

		ret = RosNode::get_topic(connector.node_id, &topic_data);
		if (ret != MROS_E_OK) {
			//TOODO ERROR LOG
			continue;
		}
		ret = RosTopic::add_data(topic_id, *topic_data);
		if (ret != MROS_E_OK) {
			//TODO ERROR LOG
		}
	}

	(void)RosTopicConnector::rel_pub_connectors(*connector_container);
	//TODO free topic_data
	return;
}

void RosTopicDataPublisher::publish(void)
{
	mRosReturnType ret;

	ret = RosTopicConnector::get_pub_topics(*topic_container);
	if (ret != MROS_E_OK) {
		return;
	}
	for (mros_uint32 i = 0; i < topic_container->size(); i++) {
		ros_topic_publish(topic_container->get(i));
	}

	return;
}

RosTopicDataPublisher::RosTopicDataPublisher()
{
	//TODO
}

RosTopicDataPublisher::~RosTopicDataPublisher()
{
	//TODO
}
