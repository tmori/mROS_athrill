#include <stdio.h>
#include <unistd.h>
#include "ros_cimpl.h"
#include "mros_os_config.h"
#include <signal.h>

void usr1_task(void)
{
	const char *data = "This is a test pub data!!";
#if 1
	int datalen = strlen(data);
	mRosObjType cobj;
	int err;
	printf("usr1_task:start\n");
	ros_init(&cobj, 0, NULL, "mros_pub_node");

	err = ros_advertise(&cobj, "test_string", 1);
	if (err != 0) {
		printf("err=%d\n", err);
	}
	else {
		printf("ok\n");
	}
	while (1) {
		usleep(1000*1000); /* 1000msec */
		ros_topic_publish(&cobj, (void*)data, datalen);
	}
#endif
	return;
}
static void callback(const char *msg)
{
	printf("callback:%s\n", msg);
	return;
}
void usr2_task(void)
{
	mRosObjType cobj;
	printf("usr2_task:start\n");
	ros_init(&cobj, 0, NULL, "mros_sub_node");

	ros_topic_subscribe(&cobj, "mros_msg", 1, callback);
	while (1) {
		usleep(1000*100); /* 100msec */
	}
	return;
}
extern void set_main_task(void);

int main(int argc, const char* argv[])
{
	signal(SIGPIPE, SIG_IGN);
	set_main_task();
	main_task();
	while (1) {
		usleep(1000*100); /* 100msec */
		cyclic_handler(0);
	}
	return 0;
}
