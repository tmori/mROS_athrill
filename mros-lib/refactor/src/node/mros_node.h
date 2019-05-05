#ifndef _MROS_NODE_H_
#define _MROS_NODE_H_

#include "mros_types.h"

namespace mros {
namespace node {

typedef enum {
	ROS_NODE_INNER = 0,
	ROS_NODE_OUTER
} RosNodeType;

class RosNode {
public:
	static mRosReturnType init(mRosSizeType max_node);
	static mRosReturnType get(const char *node_name, RosNodeIdType &id);
	static mRosReturnType create_node(const char *node_name, RosNodeType type, RosNodeIdType &id);
	static mRosReturnType create_node(const char *node_name, RosNodeType type);
	static mRosReturnType remove(const char *node_name);
	static mRosReturnType remove(RosNodeIdType id);

	static mRosReturnType send(RosNodeIdType id, char *data, mRosSizeType datalen, mRosSizeType &rlen);

private:
	RosNode();
	~RosNode();
};

}
}

#endif /* _MROS_NODE_H_ */
