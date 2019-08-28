#include <stdio.h>
#include <unistd.h>
#include "ros_cimpl.h"
#include "mros_os_config.h"

void usr1_task(void)
{
	mRosObjType cobj;
	printf("usr1_task:start\n");
	ros_init(&cobj, 0, NULL, "mros_node");
	//TODO
	return;
}
void usr2_task(void)
{
	//TODO
	printf("usr2_task:start\n");
	return;
}
extern void set_main_task(void);

int main(int argc, const char* argv[])
{
	set_main_task();
	main_task();
	while (1) {
		usleep(1000*100); /* 100msec */
		printf("main:sleep\n");
		cyclic_handler(0);
		printf("main:wakedup\n");
	}
	return 0;
}
