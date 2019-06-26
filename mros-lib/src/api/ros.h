#ifndef _ROS_H_
#define _ROS_H_

#include <string>
#include "mros_types.h"
#include <stdlib.h>

namespace std_msgs{
class String{
public:
	std::string data;
};
}


namespace ros {

void init(int argc, char *argv, std::string& node_name);


class Publisher {
public:
	void publish(std_msgs::String& data);
	void set(mRosContainerObjType cobj)
	{
		this->cobj = cobj;
	}
	mRosContainerObjType get()
	{
		return this->cobj;
	}
private:
	mRosContainerObjType cobj;
};

class Subscriber {
public:
	void set(mRosContainerObjType cobj)
	{
		this->cobj = cobj;
	}
	mRosContainerObjType get()
	{
		return this->cobj;
	}
private:
	mRosContainerObjType cobj;
};


class NodeHandle {
public:
	Subscriber subscriber(std::string& topic, int queue_size, void(*fp)(std::string*));
	Publisher advertise(std::string& topic, int queue_size);
};

}


#endif /* _ROS_H_ */
