#include <stdio.h>
#include <unistd.h>
#include "ros_cimpl.h"
#include <signal.h>
#include "athrill_mros_device.h"

#if 0
static void callback(const char *msg)
{
	static char buffer[1024];
	mRosCallbackTopicIdType topic_id;
	mRosCallbackDataLenType datalen;

	ros_topic_callback_lock();
	{
		topic_id = ros_topic_callback_topic_id();
		datalen = ros_topic_callback_datalen();
		memcpy(buffer, msg, datalen);
		buffer[datalen] = '\0';
		printf("callback:topic_id=%u:datalen=%u: %s\n", topic_id, datalen, buffer);
	}
	ros_topic_callback_unlock();
	return;
}
#endif

#define MROS_PUB_REQ_NUM	2
#define MROS_SUB_REQ_NUM	2
static AthrillMrosDevPubReqType pub_req_table[MROS_PUB_REQ_NUM] = {
		{ .topic_name = "CANID_0x100", .pub = NULL },
		{ .topic_name = "CANID_0x101", .pub = NULL },
};
static AthrillMrosDevSubReqType sub_req_table[MROS_SUB_REQ_NUM] = {
		{ .topic_name = "CANID_0x400", .sub = NULL, .callback = NULL, .sub = NULL },
		{ .topic_name = "CANID_0x404", .sub = NULL, .callback = NULL, .sub = NULL },
};


int main(int argc, const char* argv[])
{
	int err;

	signal(SIGPIPE, SIG_IGN);
	set_athrill_task();
	err = athrill_mros_device_pub_register(pub_req_table, MROS_PUB_REQ_NUM);
	if (err < 0) {
		printf("error: athrill_mros_device_pub_register()\n");
		return -1;
	}
	err = athrill_mros_device_sub_register(sub_req_table, MROS_SUB_REQ_NUM);
	if (err < 0) {
		printf("error: athrill_mros_device_sub_register()\n");
		return -1;
	}
	err = athrill_mros_device_start();
	if (err < 0) {
		printf("error: athrill_mros_device_start()\n");
		return -1;
	}
	while (1) {
		usleep(1000*100); /* 100msec */
	}
#if 0
	int datalen;
	const char *data = "This is a test pub data!!";
	mRosPublisherType *pub_cobj;
	mRosSubscriberType *sub_cobj;
	int count = 0;
	datalen = strlen(data);

	set_main_task();
	main_task();
	ros_init(0, NULL, "mros_pub_node");

	pub_cobj = ros_topic_advertise("test_string", 1);
	if (pub_cobj == NULL) {
		printf("ros_advertise():err=%d\n", -1);
	}
	else {
		printf("ros_advertise();ok\n");
	}
	sub_cobj = ros_topic_subscribe("mros_msg", 1, callback);
	if (sub_cobj == NULL) {
		printf("ros_topic_subscribe():err=%d\n", -1);
	}
	else {
		printf("ros_topic_subscribe():ok\n");
	}
	while (1) {
		usleep(1000*100); /* 100msec */
		cyclic_handler(0);
		if ((count % 10) == 0) {
			ros_topic_publish(pub_cobj, (void*)data, datalen);
		}
		count++;
	}
#endif
	return 0;
}
