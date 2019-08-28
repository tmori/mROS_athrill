#include "mros_os.h"
#include "mros_exclusive_ops.h"
#define _OPEN_THREADS
#include "kernel.h"

void mros_exclusive_init(mRosExclusiveObjectType *exobj, mRosTaskPriorityType priority)
{
	return;
}

void mros_exclusive_lock(mRosExclusiveObjectType *exobj, mROsExclusiveUnlockObjType *unlock_obj)
{
	pthread_mutex_lock(&mutex_lock);
	int tskid = get_tskid();
	os_task_table[tskid].lock_count++;
	return;
}

void mros_exclusive_unlock(mROsExclusiveUnlockObjType *unlock_obj)
{
	int tskid = get_tskid();
	os_task_table[tskid].lock_count--;
	pthread_mutex_unlock(&mutex_lock);
	return;
}
