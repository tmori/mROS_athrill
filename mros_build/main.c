#include <stdio.h>
#include <unistd.h>
#include "ros_cimpl.h"
#include "mros_os_config.h"
#include <signal.h>

static void callback(const char *msg)
{
	printf("callback:%s\n", msg);
	return;
}
extern void set_main_task(void);

int main(int argc, const char* argv[])
{
	int datalen;
	const char *data = "This is a test pub data!!";
	int err;
	mRosObjType pub_cobj;
	mRosObjType sub_cobj;
	int count = 0;
	datalen = strlen(data);

	signal(SIGPIPE, SIG_IGN);
	set_main_task();
	main_task();
	ros_init(0, NULL, "mros_pub_node");
	err = ros_topic_advertise(&pub_cobj, "test_string", 1);
	if (err != 0) {
		printf("ros_advertise():err=%d\n", err);
	}
	else {
		printf("ros_advertise();ok\n");
	}
	err = ros_topic_subscribe(&sub_cobj, "mros_msg", 1, callback);
	if (err != 0) {
		printf("ros_topic_subscribe():err=%d\n", err);
	}
	else {
		printf("ros_topic_subscribe():ok\n");
	}
	while (1) {
		usleep(1000*100); /* 100msec */
		cyclic_handler(0);
		if ((count % 10) == 0) {
			ros_topic_publish(&pub_cobj, (void*)data, datalen);
		}
		count++;
	}
	return 0;
}
