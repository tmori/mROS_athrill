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

void mros_client_wait(mRosExclusiveObjectType *ex_obj, mRosWaitListEntryType *wait_entry)
{
	mros_sleep_task();

	//TODO 起床した時にスリープ時点のタスクプライオリティかどうか不明なので要調査
	mros_change_taskpri(ex_obj->priority);
	ex_obj->task_priority = wait_entry->data.task_priority;
	return;
}

void mros_client_wakeup(mRosWaitListEntryType *wait_entry)
{
	mros_wakeup_task(wait_entry->data.task_id);
	return;
}

void mros_server_queue_init(mRosWaitQueueType *wait_queue)
{
	wait_queue->task_id = mros_get_taskid();
	wait_queue->task_priority = mros_get_taskpri();
	List_InitEmpty(&wait_queue->head, mRosWaitListEntryType);
	return;
}

void mros_server_queue_put(mRosWaitQueueType *wait_queue, mRosWaitListEntryType *wait_entry)
{
	ListEntry_AddEntry(&wait_queue->head, wait_entry);
	return;
}

mRosWaitListEntryType *mros_server_queue_get(mRosWaitQueueType *wait_queue)
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
void mros_server_queue_wait(mRosExclusiveObjectType *ex_obj, mRosWaitQueueType *wait_queue)
{
	mros_sleep_task();

	//TODO 起床した時にスリープ時点のタスクプライオリティかどうか不明なので要調査
	mros_change_taskpri(ex_obj->priority);
	ex_obj->task_priority = wait_queue->task_priority;
	return;
}

void mros_server_queue_wakeup(mRosWaitQueueType *wait_queue)
{
	mros_wakeup_task(wait_queue->task_id);
	return;
}
