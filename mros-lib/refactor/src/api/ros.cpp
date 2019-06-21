#include "ros.h"
#include "mros_node.h"

using namespace ros;
using namespace mros;
using namespace mros::node;


void init(int argc, char *argv, std::string& node_name)
{
	mRosNodeIdType id;
	//TODO
	mRosReturnType ret = RosNode::create(node_name.c_str(), ROS_NODE_TYPE_INNER,  id);

	return;
}

Subscriber NodeHandle::subscriber(std::string& topic, int queue_size, void(*fp)(std::string*))
{
	Subscriber sub;
	//TODO
	return sub;
}

Publisher NodeHandle::advertise(std::string& topic, int queue_size)
{
	Publisher pub;
	//TODO
	return pub;
}


void Publisher::publish(std_msgs::String& data)
{
	//TODO
	return;
}
