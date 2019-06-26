#ifndef _MROS_NODE_H_
#define _MROS_NODE_H_

#include "mros_types.h"
#include "mros_memory.h"

namespace mros {
namespace node {

typedef enum {
	ROS_NODE_TYPE_INNER = 0,
	ROS_NODE_TYPE_OUTER,
	ROS_NODE_TYPE_NUM,
} RosNodeType;

class RosNode {
public:
	static mRosReturnType init(mRosSizeType max_node);
	static mRosReturnType get(const char *node_name, mRosNodeIdType &id);
	static mRosReturnType type(mRosNodeIdType id, RosNodeType &type);
	static mRosReturnType create(const char *node_name, RosNodeType type, mRosNodeIdType &id);
	static mRosReturnType create(const char *node_name, RosNodeType type);
	static mRosReturnType remove(const char *node_name);
	static mRosReturnType remove(mRosNodeIdType id);

	static mRosReturnType put_pub_topic(mRosNodeIdType id, memory::mRosMemoryListEntryType &topic_data);
	static mRosReturnType get_pub_topic(mRosNodeIdType id, memory::mRosMemoryListEntryType **topic_data);

	static mRosReturnType put_sub_topic(mRosNodeIdType id, memory::mRosMemoryListEntryType &topic_data, mRosFuncIdType func_id);
	static mRosReturnType get_sub_topic(mRosNodeIdType id, memory::mRosMemoryListEntryType **topic_data);

private:
	RosNode();
	~RosNode();
};

}
}

#endif /* _MROS_NODE_H_ */
