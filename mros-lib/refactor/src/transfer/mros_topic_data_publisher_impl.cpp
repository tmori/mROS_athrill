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
	topic_container = new PrimitiveContainer<RosTopicConnectorIdType>(10); //TODO;
	connector_container = new PrimitiveContainer<RosTopicConnectorIdType>(10); //TODO;

	return MROS_E_OK;
}

static void ros_topic_publish(RosTopicIdType topic_id)
{
	mRosReturnType ret;
	RosTopicConnectorType connector;
	mRosMemoryListEntryType *topic_data;
	mRosSizeType rlen;

	ret = RosTopicConnector::get_pub_connectors(topic_id, *connector_container);
	if (ret != MROS_E_OK) {
		return;
	}

	for (mros_uint32 i = 0; i < connector_container->size(); i++) {
		ret = RosTopicConnector::get(connector_container->get(i), connector);
		if (ret != MROS_E_OK) {
			//TOODO ERROR LOG
			continue;
		}
		ret = RosTopic::get_data(topic_id, &topic_data);
		if (ret != MROS_E_OK) {
			//TOODO ERROR LOG
			continue;
		}

		ret = RosNode::send(connector.dst_id, topic_data->data.memp, topic_data->data.size, rlen);
		if (ret != MROS_E_OK) {
			//TOODO ERROR LOG
			continue;
		}
		//TODO free topic_data
	}


	(void)RosTopicConnector::rel_connectors(*connector_container);
	return;
}

void RosTopicDataPublisher::publish(void)
{
	mRosReturnType ret;

	ret = RosTopic::get_topics(*topic_container);
	if (ret != MROS_E_OK) {
		return;
	}
	for (mros_uint32 i = 0; i < topic_container->size(); i++) {
		ros_topic_publish(topic_container->get(i));
	}
	(void)RosTopic::rel_topics(*topic_container);

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
