#include "app.h"
#include "../mros-lib/ros.h"

//mbed library 
#include "mbed.h"
#include "EthernetInterface.h"

#include <iostream>
#include <sstream>

/*****mROS user task code*******/
void usr_task1(void)
{
	syslog(LOG_NOTICE,"========Activate user task1========");
	int argc = 0;
	char *argv = NULL;
	ros::init(argc,argv,"mros_node");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise("mros_msg", 1);
	ros::Rate loop_rate(5);

	std::ostringstream oss;
	std_msgs::String str;

	syslog(LOG_NOTICE,"Data Publish Start");
	while(1){
		wait_ms(1000);
		oss << "Distance[" << 10 << "]cm" << endl;
		str.data = oss.str();
		chatter_pub.publish(str);
		loop_rate.sleep();
	}
}


/*******  callback **********/
void Callback(string &msg){	
	syslog(LOG_NOTICE,"I heard [%s]",msg.c_str());
}

/*****mROS user task code*******/
void usr_task2(void)
{
	syslog(LOG_NOTICE,"========Activate user task2========");
	int argc = 0;
	char *argv = NULL;
	ros::init(argc,argv,"mros_node2");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscriber("test_string",1, Callback);
	ros::spin();
}
