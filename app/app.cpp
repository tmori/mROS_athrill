#include "app.h"
#include "../mros-lib/src/api/ros.h"
#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "mbed.h"

#include <iostream>
#include <sstream>

unsigned int athrill_device_func_call __attribute__ ((section(".athrill_device_section")));

/*****mROS user task code*******/
void usr_task1(void)
{
	syslog(LOG_NOTICE,"========Activate user task1========");
	int argc = 0;
	char *argv = NULL;
	int i = 0;
	ros::init(argc, argv, "mros_node");
	ros::NodeHandle n;
	ros::Publisher chatter_pub = n.advertise("mros_msg", 1);
	//ros::Rate loop_rate(5);
	char buf[128];

	std_msgs::String str;

	syslog(LOG_NOTICE,"Data Publish Start");
	while(1){
		wait_ms(1000);
		sprintf(buf, "publish test data(%u)", i++);
		syslog(LOG_NOTICE,"Data Publish %s", buf);
		str.data = buf;
		chatter_pub.publish(str);
		//loop_rate.sleep();
	}
}


/*******  callback **********/
void Callback(std::string *msg){
	syslog(LOG_NOTICE,"I heard [%s]",msg->c_str());
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
	//ros::spin();
}
