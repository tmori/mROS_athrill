#include <stdio.h>
#include "ros_cimpl.h"

int main(int argc, const char* argv[])
{
	mRosObjType cobj;
	ros_init(&cobj, 0, NULL, "mros_node");

	return 0;
}
