#ifndef _MROS_EXCLUSIVE_OPS_H_
#define _MROS_EXCLUSIVE_OPS_H_

#include "mros_types.h"
#include "mros_os.h"
#include "mros_list.h"


typedef struct {
	/*
	 * 排他エリアのプライオリティ
	 * 排他エリア内では，タスクのプライオリティは本プライオリティに引き上げられる
	 */
	mRosTaskPriorityType	priority;
	/*
	 * 排他エリア内に入っているタスクプライオリティ
	 * 排他エリアから復帰する際に使用する
	 */
	mRosTaskPriorityType	task_priority;
} mRosExclusiveObjectType;

extern void mros_exclusive_init(mRosExclusiveObjectType *exobj, mRosTaskPriorityType priority);
extern void mros_exclusive_lock(mRosExclusiveObjectType *exobj);
extern void mros_exclusive_unlock(mRosExclusiveObjectType *exobj);

#endif /* _MROS_EXCLUSIVE_OPS_H_ */
