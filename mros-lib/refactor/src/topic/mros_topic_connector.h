#ifndef _MROS_TOPIC_CONNECTOR_H_
#define _MROS_TOPIC_CONNECTOR_H_

#include "primitive_container.h"
#include "mros_topic.h"

namespace mros {
namespace topic {
namespace topology {

typedef struct {
	RosTopicIdType				topic_id;
	RosNodeIdType				src_id;
	RosNodeIdType				dst_id;
	RosFuncIdType				func_id;
} RosTopicConnectorType;

class RosTopicConnector {
public:
	static mRosReturnType init(mRosSizeType max_connector);
	static mRosReturnType get_connectors(RosTopicIdType topic_id, PrimitiveContainer<RosTopicConnectorIdType> &container);
	static mRosReturnType get_pub_connectors(RosTopicIdType topic_id, PrimitiveContainer<RosTopicConnectorIdType> &container);
	static mRosReturnType get_sub_connectors(RosTopicIdType topic_id, PrimitiveContainer<RosTopicConnectorIdType> &container);
	static mRosReturnType rel_connectors(PrimitiveContainer<RosTopicConnectorIdType> &container);
	static mRosReturnType get(RosTopicConnectorIdType id, RosTopicConnectorType &connector);

	static mRosReturnType add_pubnode_topic(const char* topic_name, RosNodeIdType src);
	static mRosReturnType add_subnode_topic(const char* topic_name, RosNodeIdType dst, RosFuncIdType func);

private:
	RosTopicConnector();
	~RosTopicConnector();
};

}
}
}


#endif /* _MROS_TOPIC_CONNECTOR_H_ */
