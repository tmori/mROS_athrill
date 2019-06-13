#ifndef _MROS_TOPIC_CONNECTOR_H_
#define _MROS_TOPIC_CONNECTOR_H_

#include "primitive_container.h"
#include "mros_topic.h"

namespace mros {
namespace topic {
namespace topology {

typedef struct {
	RosTopicIdType				topic_id;
	RosNodeIdType				node_id;
	RosFuncIdType				func_id;
} RosTopicConnectorType;

class RosTopicConnector {
public:
	static mRosReturnType init(mRosSizeType max_pub_connector, mRosSizeType max_sub_connector);

	static mRosReturnType get_pub_topics(PrimitiveContainer<RosTopicIdType> &container);
	static mRosReturnType get_sub_topics(PrimitiveContainer<RosTopicIdType> &container);

	static mRosReturnType get_pub_connectors(RosTopicIdType topic_id, PrimitiveContainer<RosTopicConnectorIdType> &container);
	static mRosReturnType rel_pub_connectors(PrimitiveContainer<RosTopicConnectorIdType> &container);
	static mRosReturnType get_sub_connectors(RosTopicIdType topic_id, PrimitiveContainer<RosTopicConnectorIdType> &container);
	static mRosReturnType rel_sub_connectors(PrimitiveContainer<RosTopicConnectorIdType> &container);

	static mRosReturnType get_pub(RosTopicConnectorIdType id, RosTopicConnectorType &connector);
	static mRosReturnType get_sub(RosTopicConnectorIdType id, RosTopicConnectorType &connector);

	static mRosReturnType add_pub(const char* topic_name, RosNodeIdType src);
	static mRosReturnType add_sub(const char* topic_name, RosNodeIdType dst, RosFuncIdType func);

private:
	RosTopicConnector();
	~RosTopicConnector();
};

}
}
}


#endif /* _MROS_TOPIC_CONNECTOR_H_ */
