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
	return;
}

void mros_exclusive_unlock(mROsExclusiveUnlockObjType *unlock_obj)
{
	pthread_mutex_unlock(&mutex_lock);
	return;
}
