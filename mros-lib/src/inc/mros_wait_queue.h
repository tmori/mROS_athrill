#ifndef _MROS_WAIT_QUEUE_H_
#define _MROS_WAIT_QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_list.h"
#include "mros_exclusive_ops.h"

typedef struct {
	mRosTaskIdType 			task_id;
	mRosTaskPriorityType 	task_priority;
	void 					*reqp;
} mRosWaitEntryType;
typedef ListEntryType(mRosWaitListEntryType, mRosWaitEntryType) mRosWaitListEntryType;
typedef ListHeadType(mRosWaitListEntryType) mRosWaitListHeadType;

typedef struct {
	mRosTaskIdType 			task_id;
	mRosTaskPriorityType 	task_priority;
	mRosWaitListHeadType	head;
} mRosWaitQueueType;

extern void mros_client_wait_entry_init(mRosWaitListEntryType *wait_entry, void *reqp);
extern void mros_client_wait(mRosExclusiveObjectType *ex_obj, mRosWaitListEntryType *wait_entry);
extern void mros_client_wakeup(mRosWaitListEntryType *wait_entry);


extern void mros_server_queue_init(mRosWaitQueueType *wait_queue);
extern void mros_server_queue_put(mRosWaitQueueType *wait_queue, mRosWaitListEntryType *wait_entry);
extern mRosWaitListEntryType *mros_server_queue_get(mRosWaitQueueType *wait_queue);
extern void mros_server_queue_wait(mRosExclusiveObjectType *ex_obj, mRosWaitQueueType *wait_queue);
extern void mros_server_queue_wakeup(mRosWaitQueueType *wait_queue);

#ifdef __cplusplus
}
#endif

#endif /* _MROS_WAIT_QUEUE_H_ */
