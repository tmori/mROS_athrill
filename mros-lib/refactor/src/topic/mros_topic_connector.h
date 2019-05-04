#ifndef _MROS_TOPIC_CONNECTOR_H_
#define _MROS_TOPIC_CONNECTOR_H_

#include "primitive_container.h"
#include "mros_topic.h"

namespace mros {
namespace topic {
namespace topology {



class RosTopicConnector {
public:
	static mRosReturnType init(mRosSizeType max_connector);
	static mRosReturnType get_topics(PrimitiveContainer<RosTopicConnectorIdType> &container);
	static mRosReturnType put_topics(PrimitiveContainer<RosTopicConnectorIdType> &container);

	static mRosReturnType add_pubnode_topic(const char* topic_name, RosNodeIdType src);
	static mRosReturnType add_subnode_topic(const char* topic_name, RosNodeIdType dst);

private:
	RosTopicConnector();
	~RosTopicConnector();
};

}
}
}


#endif /* _MROS_TOPIC_CONNECTOR_H_ */
