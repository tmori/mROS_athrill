#include "mros_os.h"
#include "mros_exclusive_ops.h"
#include <stdlib.h>

void mros_exclusive_init(mRosExclusiveObjectType *exobj, mRosTaskPriorityType priority)
{
	exobj->priority = priority;
	exobj->task_priority = 0;
	return;
}

void mros_exclusive_lock(mRosExclusiveObjectType *exobj)
{
	mRosTaskPriorityType priority = mros_get_taskid();
	mros_change_taskpri(exobj->priority);
	exobj->task_priority = priority;
	return;
}

void mros_exclusive_unlock(mRosExclusiveObjectType *exobj)
{
	mros_change_taskpri(exobj->task_priority);
	return;
}
