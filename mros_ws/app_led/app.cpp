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
#include "digital.h"
#include "device_io.h"

using namespace std;

unsigned int athrill_device_func_call __attribute__ ((section(".athrill_device_section")));


static volatile int led_state = 0;
/*
 * 0.5 sec cycle
 */
void sample_program(uint8 led_bit)
{
    uint8 data = sil_reb_mem(DIGITAL_REG_ADDR);

    if ((data & led_bit) != 0) {
        data &= ~led_bit;
        sil_wrb_mem(DIGITAL_REG_ADDR, data);
        led_state = 0;
    }
    else {
        data |= led_bit;
        sil_wrb_mem(DIGITAL_REG_ADDR, data);
        led_state = 1;
    }
    return;
}
/*******  callback **********/
#include <string.h>
void Callback1(std_msgs::String *msg)
{
	sample_program(DIGITAL_LED1);
}
void Callback2(std_msgs::String *msg)
{
	sample_program(DIGITAL_LED2);
}

/*****mROS user task code*******/
static char str_buf[256];
void usr_task1(void)
{
	syslog(LOG_NOTICE,"========Activate user task1========");
	int argc = 0;
	char *argv = NULL;
	ros::init(argc,argv,"mros_node");
	ros::NodeHandle n;
	ros::Publisher chatter_pub;
	ros::Rate loop_rate(10);
	std_msgs::String str;

	chatter_pub = n.advertise<std_msgs::String>("mros_msging", 1);
	syslog(LOG_NOTICE,"LED STATE Publish Start");
	while(1){
		sprintf(str_buf, "LED_STATE : %u", led_state);
		str.data = string(str_buf);
		chatter_pub.publish(str);
		loop_rate.sleep();
	}
}



/*****mROS user task code*******/
void usr_task2(void)
{
	syslog(LOG_NOTICE,"========Activate user task2========");
	int argc = 0;
	char *argv = NULL;
	ros::init(argc,argv,"led1_node");
	ros::NodeHandle n;
	ros::Subscriber sub;

	 sub = n.subscribe("led1_toggle",1, Callback1);

	ros::spin();
}
