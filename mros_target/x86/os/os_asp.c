typedef int* intptr_t;
#include "kernel.h"
#include "kernel_cfg.h"
#include <time.h>
#include "mros_os_config.h"

pthread_mutex_t mutex_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_wait = PTHREAD_COND_INITIALIZER;

extern void usr1_task(void);
extern void usr2_task(void);


typedef struct {
	void (*task_func) (void);
} OsTaskFuncType;

static void *os_asp_task_body(void *arg)
{
	void (*fp)(void);
	fp = (void (*)(void))arg;
	fp();
	return NULL;
}
static OsTaskFuncType os_task_table[NUM_TASK] = {
		{ main_task },
		{ sub_task },
		{ pub_task },
		{ xml_slv_task },
		{ xml_mas_task },
		{ usr1_task },
		{ usr2_task },
};

int slp_tsk(void)
{
	pthread_mutex_lock(&mutex_lock);
	pthread_cond_wait(&cond_wait, &mutex_lock);
	pthread_mutex_unlock(&mutex_lock);
	return 0;
}
int act_tsk(ID id)
{
	pthread_t ptr;

	return pthread_create(&ptr, NULL, os_asp_task_body, (void*)os_task_table[id].task_func);
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
	pthread_cond_timedwait(&cond_wait, &mutex_lock, &tv);
	pthread_mutex_unlock(&mutex_lock);
	return 0;
}
int wup_tsk(ID tskid)
{
	pthread_mutex_lock(&mutex_lock);
	pthread_cond_signal(&cond_wait);
	pthread_mutex_unlock(&mutex_lock);
	return 0;
}
