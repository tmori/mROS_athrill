#include "mros_wait_queue.h"
#include "mros_os.h"
#include "mros_list.h"
#include <stdlib.h>

void mros_client_wait_entry_init(mRosWaitListEntryType *wait_entry, void *reqp)
{
	wait_entry->data.reqp = reqp;
	wait_entry->data.task_id = mros_get_taskid();
	wait_entry->data.task_priority = mros_get_taskpri();
	return;
}

void mros_server_queue_init(mRosWaitQueueType *wait_queue)
{
	wait_queue->task_id = mros_get_taskid();
	List_InitEmpty(&wait_queue->head, mRosWaitListEntryType);

	return;
}

void mros_client_wakeup(mRosWaitListEntryType *wait_entry)
{
	mros_wakeup_task(wait_entry->data.task_id);
	return;
}


void mros_client_put_request(mRosWaitQueueType *wait_queue, mRosWaitListEntryType *wait_entry)
{
	ListEntry_AddEntry(&wait_queue->head, wait_entry);
	mros_wakeup_task(wait_queue->task_id);
	return;
}

void mros_client_wait_for_request_done(mRosWaitQueueType *wait_queue, mRosWaitListEntryType *wait_entry)
{
	mros_client_put_request(wait_queue, wait_entry);
	mros_sleep_task();
	return;
}
static mRosWaitListEntryType *mros_server_queue_get(mRosWaitQueueType *wait_queue)
{
	mRosTaskPriorityType min_priority = 0;
	mRosWaitListEntryType *entry;
	mRosWaitListEntryType *target = NULL;

	ListEntry_Foreach(&wait_queue->head, entry) {
		if (entry->data.task_priority > min_priority) {
			min_priority = entry->data.task_priority;
			target = entry;
		}
	}
	if (target != NULL) {
		ListEntry_RemoveEntry(&wait_queue->head, target);
	}
	return target;
}

mRosWaitListEntryType *mros_server_queue_wait(mRosWaitQueueType *wait_queue)
{
	mros_sleep_task();

	if (wait_queue->head.entry_num > 0) {
		return mros_server_queue_get(wait_queue);
	}
	return NULL;
}
