#include "mros_exclusive_area.h"
#include "mros_wait_queue.h"
#include "mros_config.h"

mRosExclusiveObjectType mros_exclusive_area;
mRosWaitQueueType mros_master_wait_queue;

mRosWaitQueueType mros_subscribe_wait_queue;

void mros_exclusive_area_init(mRosTaskIdType mas_task_id, mRosTaskIdType sub_task_id)
{
	mros_exclusive_init(&mros_exclusive_area, MROS_GIANT_EXCLUSIVE_AREA_PRIORITY);
	mros_server_queue_init(&mros_master_wait_queue, mas_task_id);
	mros_server_queue_init(&mros_subscribe_wait_queue, sub_task_id);

	return;
}
