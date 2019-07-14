#include "app.h"
#include "../mros-lib/src/api/ros.h"
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


/*
 * 0.5 sec cycle
 */
void sample_program(uint8 led_bit)
{
    uint8 data = sil_reb_mem(DIGITAL_REG_ADDR);

    if ((data & led_bit) != 0) {
        data &= ~led_bit;
        sil_wrb_mem(DIGITAL_REG_ADDR, data);
    }
    else {
        data |= led_bit;
        sil_wrb_mem(DIGITAL_REG_ADDR, data);
    }
    return;
}
/*******  callback **********/
#include <string.h>
static char callback_buffer1[1024];
static char callback_buffer2[1024];
void Callback1(string *msg)
{
	sprintf(callback_buffer1, "I heard [%s]",msg->c_str());
	syslog(LOG_NOTICE, "%s", callback_buffer1);
	sample_program(DIGITAL_LED1);
}
void Callback2(string *msg)
{
	sprintf(callback_buffer2, "I heard [%s]",msg->c_str());
	syslog(LOG_NOTICE, "%s", callback_buffer2);
	sample_program(DIGITAL_LED2);
}

/*****mROS user task code*******/

void usr_task1(void)
{
	syslog(LOG_NOTICE,"========Activate user task1========");
	int argc = 0;
	char *argv = NULL;
	ros::init(argc,argv,"led2_node");
	ros::NodeHandle n;
	ros::Subscriber sub;

	 sub = n.subscriber("led2_toggle",1, Callback2);

	ros::spin();
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

	 sub = n.subscriber("led1_toggle",1, Callback1);

	ros::spin();
}
