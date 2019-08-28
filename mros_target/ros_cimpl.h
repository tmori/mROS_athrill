#ifndef _ROS_CIMPL_H_
#define _ROS_CIMPL_H_

typedef struct {
	int id;
	void *objp;
} mRosObjType;

extern void ros_init(mRosObjType *cobj, int argc, char *argv, const char* node_name);
extern int ros_subscribe(mRosObjType *cobj, const char* topic, int queue_size, void (*fp) (char *));
extern int ros_advertise(mRosObjType *cobj, const char* topic, int queue_size);
extern int ros_publish(mRosObjType* cobj, void *data, int datalen);

#include "mros_log.h"

#endif /* _ROS_CIMPL_H_ */