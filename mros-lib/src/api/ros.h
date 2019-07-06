#ifndef _ROS_H_
#define _ROS_H_

#include <string>

namespace std_msgs{
class String{
public:
	std::string data;
};
}


namespace ros {

void init(int argc, char *argv, std::string node_name);


class Publisher {
public:
	void publish(std_msgs::String& data);
	void set(void *cobj)
	{
		this->cobj = cobj;
	}
	void* get()
	{
		return this->cobj;
	}
private:
	void *cobj;
};

class Subscriber {
public:
	void set(void *cobj)
	{
		this->cobj = cobj;
	}
	void* get()
	{
		return this->cobj;
	}
private:
	void *cobj;
};


class NodeHandle {
public:
	Subscriber subscriber(std::string topic, int queue_size, void(*fp)(std::string*));
	Publisher advertise(std::string topic, int queue_size);
};

}


#endif /* _ROS_H_ */
