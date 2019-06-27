#include "mros_os_target.h"
#include "mros_protocol_master_cimpl.h"
#include "mros_protocol_slave_cimpl.h"
#include "mros_protocol_subscribe_cimpl.h"
#include "mros_protocol_publish_cimpl.h"

mRosTaskIdType mros_get_taskid(void)
{
	mRosTaskIdType tid;
	(void)get_tid(&tid);
	return tid;
}

mRosTaskPriorityType mros_get_taskpri(void)
{
	mRosTaskIdType tid;
	PRI pri;
	(void)get_tid(&tid);
	(void)get_pri(tid, &pri);
	return pri;
}

void mros_change_taskpri(mRosTaskPriorityType priority)
{
	mRosTaskIdType tid;
	(void)get_tid(&tid);
	 chg_pri(tid, priority);
	 return;
}

void mros_sleep_task(void)
{
	(void)slp_tsk();
}

void mros_wakeup_task(mRosTaskIdType task_id)
{
	(void)wup_tsk(task_id);
}

void main_task()
{
	mros_protocol_subscribe_init();
	mros_protocol_publish_init();
	mros_protocol_slave_init();
	mros_protocol_master_init();
	return;
}

void sub_task()
{
	mros_protocol_subscribe_run();
	return;
}

void pub_task()
{
	mros_protocol_publish_run();
	return;
}

void xml_slv_task()
{
	mros_protocol_slave_run();
	return;
}

void xml_mas_task()
{
	mros_protocol_master_run();
	return;
}

void cyclic_handler(intptr_t exinf)
{
	//iwup_tsk(SUB_TASK);
	//iwup_tsk(XML_SLV_TASK);
	return;
}

