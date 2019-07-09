#include "app.h"
#include "../mros-lib/src/api/ros.h"
//mbed library
#include "mbed.h"
#include "EthernetInterface.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

unsigned int athrill_device_func_call __attribute__ ((section(".athrill_device_section")));

/*****mROS user task code*******/
static char str_buf[1024];

void usr_task1(void)
{
	syslog(LOG_NOTICE,"========Activate user task1========");
	int argc = 0;
	char *argv = NULL;
	int i = 0;
	ros::init(argc,argv,"mros_node");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise("mros_msg", 1);
	ros::Rate loop_rate(5);

	std_msgs::String str;

	syslog(LOG_NOTICE,"Data Publish Start");
	while(1){
		wait_ms(1000);
		sprintf(str_buf, "publish test data(%u)", i++);
		str.data = string(str_buf);
		chatter_pub.publish(str);
		loop_rate.sleep();
	}
}


/*******  callback **********/
#include <string.h>
static char callback_buffer[1024];
void Callback(string *msg){
	sprintf(callback_buffer, "I heard [%s]",msg->c_str());
	syslog(LOG_NOTICE, "%s", callback_buffer);
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
