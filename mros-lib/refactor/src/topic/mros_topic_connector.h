#ifndef _MROS_TOPIC_CONNECTOR_H_
#define _MROS_TOPIC_CONNECTOR_H_

#include "primitive_container.h"
#include "mros_topic.h"

namespace mros {
namespace topic {
namespace topology {

typedef struct {
	mRosTopicIdType				topic_id;
	mRosNodeIdType				node_id;
	mRosFuncIdType				func_id;
} RosTopicConnectorType;

class RosTopicConnector {
public:
	static mRosReturnType init(mRosSizeType max_pub_connector, mRosSizeType max_sub_connector);

	static mRosReturnType get_pub_topics(PrimitiveContainer<mRosTopicIdType> &container);
	static mRosReturnType get_sub_topics(PrimitiveContainer<mRosTopicIdType> &container);

	static mRosReturnType get_pub_connectors(mRosTopicIdType topic_id, PrimitiveContainer<mRosTopicConnectorIdType> &container);
	static mRosReturnType rel_pub_connectors(PrimitiveContainer<mRosTopicConnectorIdType> &container);
	static mRosReturnType get_sub_connectors(mRosTopicIdType topic_id, PrimitiveContainer<mRosTopicConnectorIdType> &container);
	static mRosReturnType rel_sub_connectors(PrimitiveContainer<mRosTopicConnectorIdType> &container);

	static mRosReturnType get_pub(mRosTopicConnectorIdType id, RosTopicConnectorType &connector);
	static mRosReturnType get_sub(mRosTopicConnectorIdType id, RosTopicConnectorType &connector);

	static mRosReturnType add_pub(const char* topic_name, mRosNodeIdType src);
	static mRosReturnType add_sub(const char* topic_name, mRosNodeIdType dst, mRosFuncIdType func);

private:
	RosTopicConnector();
	~RosTopicConnector();
};

}
}
}


#endif /* _MROS_TOPIC_CONNECTOR_H_ */
