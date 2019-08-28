#include "app.h"
#include "../../../../fork/mROS/mros-lib/mros-src/api/ros.h"
#include "../../../../fork/mROS/mros-lib/mros-msgs/std_msgs/String.h"
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
extern "C" {
unsigned char test_inner = 1;
}
/*******  callback **********/
#include <string.h>
static char callback_buffer1[1024];
void Callback1(std_msgs::String *msg){
	sprintf(callback_buffer1, "I(1) heard [%s]",msg->data.c_str());
	syslog(LOG_NOTICE, "%s", callback_buffer1);
}
static char callback_buffer2[1024];
void Callback2(std_msgs::String *msg){
	sprintf(callback_buffer2, "I(2) heard [%s]",msg->data.c_str());
	syslog(LOG_NOTICE, "%s", callback_buffer2);
}

void usr_task1(void)
{
	syslog(LOG_NOTICE,"========Activate user task1========");
	int argc = 0;
	char *argv = NULL;
	int i = 0;
	ros::init(argc,argv,"mros_node");
	ros::NodeHandle n;
	ros::Publisher chatter_pub1;
	ros::Rate loop_rate(5);
	std_msgs::String str;
	ros::Subscriber sub;

	 sub = n.subscribe("test_string2",1, Callback2);

	chatter_pub1 = n.advertise<std_msgs::String>("test_string1", 1);
	syslog(LOG_NOTICE,"Data Publish Start");
	while(1){
		wait_ms(1000);
		sprintf(str_buf, "publish test data(%u)", i++);
		syslog(LOG_NOTICE, "%s", str_buf);
		str.data = string(str_buf);
		chatter_pub1.publish(str);
		loop_rate.sleep();
	}
}



/*****mROS user task code*******/
#if 0
void usr_task2(void)
{
	syslog(LOG_NOTICE,"========Activate user task2========");
	int argc = 0;
	char *argv = NULL;
	ros::init(argc,argv,"mros_node2");
	ros::NodeHandle n;
	ros::Subscriber sub;

	 sub = n.subscribe("test_string1",1, Callback1);
	 sub = n.subscribe("test_string2",1, Callback2);

	ros::spin();
}
#else
void usr_task2(void)
{
	syslog(LOG_NOTICE,"========Activate user task2========");
#if 0
	int argc = 0;
	char *argv = NULL;
	int i = 0;
	ros::init(argc,argv,"mros_node2");
	ros::NodeHandle n;
	ros::Publisher chatter_pub;
	ros::Rate loop_rate(5);
	std_msgs::String str;
	ros::Subscriber sub;

	 sub = n.subscribe("test_string1",1, Callback1);

	chatter_pub = n.advertise<std_msgs::String>("test_string2", 1);
	syslog(LOG_NOTICE,"user task2:Data Publish Start");
	while(1){
		wait_ms(500);
		sprintf(str_buf, "user task2:publish test data(%u)", i++);
		syslog(LOG_NOTICE, "%s", str_buf);
		str.data = string(str_buf);
		chatter_pub.publish(str);
		loop_rate.sleep();
	}
#endif
}

#endif
