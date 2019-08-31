#ifndef _ROS_CIMPL_H_
#define _ROS_CIMPL_H_

typedef struct {
	void *objp;
} mRosObjType;

extern void ros_init(int argc, char *argv, const char* node_name);
extern int ros_topic_subscribe(mRosObjType *cobj, const char* topic, int queue_size, void (*fp) (const char *));
extern int ros_topic_advertise(mRosObjType *cobj, const char* topic, int queue_size);
extern int ros_topic_publish(mRosObjType* cobj, void *data, int datalen);

typedef unsigned int mRosCallbackTopicIdType;
typedef unsigned int mRosCallbackDataLenType;
extern mRosCallbackTopicIdType ros_topic_callback_topic_id(void);
extern mRosCallbackDataLenType ros_topic_callback_datalen(void);

#include "mros_log.h"

#endif /* _ROS_CIMPL_H_ */
