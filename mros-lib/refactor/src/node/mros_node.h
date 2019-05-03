#ifndef _MROS_NODE_H_
#define _MROS_NODE_H_

#include "mros_types.h"

namespace mros {
namespace node {

class RosNode {
public:
	RosNode(const char *name);
	RosNodeIdType id()
	{
		return node_id;
	}
	~RosNode();

private:
	RosNodeIdType	node_id;
	const char		*node_name;

};

}
}

#endif /* _MROS_NODE_H_ */
