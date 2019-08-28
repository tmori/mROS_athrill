typedef int* intptr_t;
#include "kernel.h"
#include "kernel_cfg.h"
#include <time.h>
#include "mros_os_config.h"

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_wait = PTHREAD_COND_INITIALIZER;

extern void usr1_task(void);
extern void usr2_task(void);



OsTaskType os_task_table[NUM_TASK] = {
		{ .task_func = main_task },
		{ .task_func = sub_task },
		{ .task_func = pub_task },
		{ .task_func = xml_slv_task },
		{ .task_func = xml_mas_task },
		{ .task_func = usr1_task },
		{ .task_func = usr2_task },
};

void set_main_task(void)
{
	pthread_mutex_lock(&mutex_lock);
	os_task_table[MAIN_TASK].thread = pthread_self();
	os_task_table[MAIN_TASK].state = OsState_RUNNING;
	os_task_table[MAIN_TASK].lock_count = 0;
	pthread_mutex_unlock(&mutex_lock);
}

int get_tskid(void)
{
	int i;
	pthread_t self = pthread_self();
	for (i = 0; i < NUM_TASK; i++) {
		if (os_task_table[i].state == OsState_STOPPED) {
			continue;
		}
		if (self == os_task_table[i].thread) {
			return i;
		}
	}
	return -1;
}
static void *os_asp_task_body(void *arg)
{
	void (*fp)(void);
	fp = (void (*)(void))arg;
	pthread_mutex_lock(&mutex_lock);
	int tskid = get_tskid();
	if (tskid >= 0) {
		os_task_table[tskid].state = OsState_RUNNING;
	}
	pthread_mutex_unlock(&mutex_lock);
	fp();
	return NULL;
}

int slp_tsk(void)
{
	/*
	 * already locked!
	 */
	int tskid = get_tskid();
	if (tskid < 0) {
		return -1;
	}
	os_task_table[tskid].state = OsState_WAITING;
	while (os_task_table[tskid].state == OsState_WAITING) {
		os_task_table[tskid].lock_count--;
		pthread_cond_wait(&cond_wait, &mutex_lock);
		os_task_table[tskid].lock_count++;
	}
	return 0;
}
int act_tsk(ID id)
{
	pthread_mutex_lock(&mutex_lock);
	int tskid = get_tskid();
	if (tskid < 0) {
		pthread_mutex_unlock(&mutex_lock);
		return -1;
	}
	os_task_table[tskid].lock_count++;
	os_task_table[id].state = OsState_RUNNABLE;
	(void)pthread_create(&os_task_table[id].thread, NULL, os_asp_task_body, (void*)os_task_table[id].task_func);
	os_task_table[tskid].lock_count--;
	pthread_mutex_unlock(&mutex_lock);
	return 0;
}
int get_tid(ID *p_tskid)
{
	return 0;
}
int chg_pri(ID tskid, PRI tskpri)
{
	//TODO
	return 0;
}
int iwup_tsk(ID tskid)
{
	pthread_mutex_lock(&mutex_lock);
	os_task_table[tskid].state = OsState_RUNNABLE;
	pthread_cond_signal(&cond_wait);
	pthread_mutex_unlock(&mutex_lock);
	return 0;
}
int get_pri(ID tskid, PRI *p_tskpri)
{
	//TODO
	*p_tskpri = 0;
	return 0;
}
int dly_tsk(int dlytim)
{
	struct timespec tv;
	clock_gettime(CLOCK_REALTIME, &tv);
	tv.tv_nsec += dlytim * 1000;
	pthread_mutex_lock(&mutex_lock);
	int tskid = get_tskid();
	if (tskid < 0) {
		pthread_mutex_unlock(&mutex_lock);
		return -1;
	}
	os_task_table[tskid].lock_count++;
	os_task_table[tskid].state = OsState_WAITING;
	pthread_cond_timedwait(&cond_wait, &mutex_lock, &tv);
	os_task_table[tskid].state = OsState_RUNNING;
	os_task_table[tskid].lock_count--;
	pthread_mutex_unlock(&mutex_lock);
	return 0;
}
int wup_tsk(ID tskid)
{
	pthread_mutex_lock(&mutex_lock);
	os_task_table[tskid].state = OsState_RUNNABLE;
	pthread_cond_signal(&cond_wait);
	pthread_mutex_unlock(&mutex_lock);
	return 0;
}
