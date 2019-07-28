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
#include <string.h>

using namespace std;

unsigned int athrill_device_func_call __attribute__ ((section(".athrill_device_section")));


typedef struct {
	struct {
		int x;
		int z;
	} pos;
	struct {
		int left;
		int right;
	} stear;
	struct {
		int left;
		int right;
	} rpm;
	struct {
		int found;
		int distance;
		int angle;
	} obstacle;
	struct {
		int light;
	} line_sensor;
} SensorInfoType;
static SensorInfoType car_sensor;

/*****mROS user task code*******/

static char str_buf[256];
#define ARG_NUM	3
typedef struct {
	int argc;
	char *fmt[ARG_NUM];
	int argv[ARG_NUM];
} PubDataArgType;
static void create_pub_data(char *ptr, PubDataArgType *argp)
{
	if (argp->argc == 1) {
		sprintf(ptr, "%s=%u", argp->fmt[0], argp->argv[0]);
	}
	else {
		sprintf(ptr, "%s=%u:%s=%u", argp->fmt[0], argp->argv[0], argp->fmt[1], argp->argv[1]);
	}
	return;
}

static char *parse_sub_data(char *ptr, int *valuep)
{
	char *p = ptr;
	char *vp = NULL;
	//find found =
	while (vp == NULL) {
		switch ((*p)) {
		case '\0':
			return NULL;
		case '=':
			p++;
			vp = p;
			break;
		default:
			p++;
		}
	}

	//find : or \0
	while ((*p) != '\0') {
		if ((*p) == ':') {
			*p = '\0';
			p++;
			break;
		}
		p++;
	}
	*valuep = atoi(vp);
	return p;
}

/*******  callback **********/
static void read_sub_data(char *ptr, PubDataArgType *argp)
{
	int i;
	char *p;
	argp->argv[0] = 0;
	argp->argv[1] = 0;
	argp->argv[2] = 0;


	p = ptr;
	for (i = 0; i < argp->argc; i++) {
		p = parse_sub_data(p, &argp->argv[i]);
		if (p == NULL) {
			break;
		}
	}
	return;
}

static void topic_publish(ros::Publisher &pub, int value)
{
	std_msgs::String str;
	PubDataArgType arg;

	arg.argc = 1;
	arg.fmt[0] = (char*)"value";
	arg.argv[0] = value;
	create_pub_data(str_buf, &arg);
	str.data = string(str_buf);
	pub.publish(str);
	return;
}

typedef struct {
	ros::Publisher motor;
	ros::Publisher stearing;
	ros::Publisher brake;
} ActuatorType;

static ActuatorType car_actuator;

void usr_task1(void)
{
	syslog(LOG_NOTICE,"========Activate user task1========");
	int argc = 0;
	char *argv = NULL;
	int i = 0;
	ros::init(argc,argv,"mros_node");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);

	car_actuator.motor = n.advertise("control_motor_torque", 1);
	car_actuator.stearing = n.advertise("control_stearing", 1);
	car_actuator.brake = n.advertise("control_brake", 1);

	topic_publish(car_actuator.motor, 10);
	while(1){
		if (car_sensor.obstacle.found != 0) {
			topic_publish(car_actuator.brake, 1);
		}
		i++;
		loop_rate.sleep();
	}
}



/*****mROS user task code*******/
void pose_callback(string *msg)
{
	PubDataArgType arg;
	arg.argc = 2;
	read_sub_data((char*)msg->c_str(), &arg);
	car_sensor.pos.x = arg.argv[0];
	car_sensor.pos.z = arg.argv[1];

	//syslog(LOG_NOTICE, "/pose x=%d y=%d", arg.argv[0], arg.argv[1]);
}
void stearing_callback(string *msg)
{
	PubDataArgType arg;
	arg.argc = 2;
	read_sub_data((char*)msg->c_str(), &arg);
	car_sensor.stear.left = arg.argv[0];
	car_sensor.stear.right = arg.argv[1];
	//syslog(LOG_NOTICE, "/stearing left_stear=%d right_stear=%d", arg.argv[0], arg.argv[1]);
}
void speed_callback(string *msg)
{
	PubDataArgType arg;
	arg.argc = 2;
	read_sub_data((char*)msg->c_str(), &arg);
	car_sensor.rpm.left = arg.argv[0];
	car_sensor.rpm.right = arg.argv[1];
	//syslog(LOG_NOTICE, "/speed left_rpm=%d right_rpm=%d", arg.argv[0], arg.argv[1]);
}
void obstacle_callback(string *msg)
{
	PubDataArgType arg;
	arg.argc = 3;
	read_sub_data((char*)msg->c_str(), &arg);
	car_sensor.obstacle.found = arg.argv[0];
	car_sensor.obstacle.distance = arg.argv[1];
	car_sensor.obstacle.angle = arg.argv[2];
	syslog(LOG_NOTICE, "/obstacle found=%d distance=%d angle=%d", arg.argv[0], arg.argv[1], arg.argv[2]);
}
void line_sensor_callback(string *msg)
{
	PubDataArgType arg;
	arg.argc = 1;
	read_sub_data((char*)msg->c_str(), &arg);
	car_sensor.line_sensor.light = arg.argv[0];
	//syslog(LOG_NOTICE, "/speed line_sensor=%d ", arg.argv[0]);
}

void usr_task2(void)
{
	syslog(LOG_NOTICE,"========Activate user task2========");
	int argc = 0;
	char *argv = NULL;
	ros::init(argc,argv,"led1_node");
	ros::NodeHandle n;
	ros::Subscriber sub;

	 //sub = n.subscriber("pose",1, pose_callback);
	 //sub = n.subscriber("stearing",1, stearing_callback);
	 //sub = n.subscriber("speed",1, speed_callback);
	 sub = n.subscriber("obstacle",1, obstacle_callback);
	 //sub = n.subscriber("line_sensor",1, line_sensor_callback);

	ros::spin();
}
