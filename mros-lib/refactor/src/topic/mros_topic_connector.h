#ifndef _MROS_TOPIC_CONNECTOR_H_
#define _MROS_TOPIC_CONNECTOR_H_

#include "primitive_container.h"
#include "mros_topic.h"

namespace mros {
namespace topology {

class RosTopicConnector {
public:
	static mRosReturnType get_publish_topics(PrimitiveContainer<RosTopicConnectorIdType> &container);
	static mRosReturnType get_subscribe_topics(PrimitiveContainer<RosTopicConnectorIdType> &container);

	static mRosReturnType put_publish_topic(const char* topic_name, RosNodeIdType src, RosNodeIdType dst);
	static mRosReturnType put_subscribe_topic(const char* topic_name, RosNodeIdType src, RosNodeIdType dst);

private:
	RosTopicConnector(RosTopicIdType topic, RosNodeIdType src, RosNodeIdType dst);
	~RosTopicConnector();

	RosTopicConnectorIdType		connector_id;
	RosTopicIdType				topic_id;
	RosNodeIdType				src_id;
	RosNodeIdType				dst_id;
};

}
}


#endif /* _MROS_TOPIC_CONNECTOR_H_ */
