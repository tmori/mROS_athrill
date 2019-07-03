#ifndef _MROS_EXCLUSIVE_AREA_H_
#define _MROS_EXCLUSIVE_AREA_H_

#include "mros_exclusive_ops.h"
#include "mros_wait_queue.h"

extern mRosExclusiveObjectType mros_exclusive_area;
extern mRosWaitQueueType mros_master_wait_queue;
extern mRosWaitQueueType mros_subscribe_wait_queue;

extern void mros_exclusive_area_init(void);

#endif /* _MROS_EXCLUSIVE_AREA_H_ */
