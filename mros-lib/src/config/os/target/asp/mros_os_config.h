#ifndef _MROS_OS_CONFIG_H_
#define _MROS_OS_CONFIG_H_

#include "kernel.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void main_task(void);
extern void sub_task(void);
extern void pub_task(void);
extern void xml_slv_task(void);
extern void xml_mas_task(void);
extern void cyclic_handler(intptr_t exinf);



/****************************************
 * kernel cfg
 ****************************************/
#ifndef MROS_USR_TASK_PRI
#define MAIN_TASK_PRI 			7
#define MROS_USR_TASK1_PRI  	8
#define MROS_USR_TASK2_PRI  	9
#define MROS_USR_TASK_PRI		8
#define MROS_TASK_PRI  			6
#endif /* ROS_USR_TASK_PRI */

#ifndef TASK_PORTID
#define	TASK_PORTID		1			/* serial port ID for something typing */
#endif /* TASK_PORTID */

#ifndef MROS_TASK_STACK_SIZE
#if 0
#define MROS_SUB_STACK_SIZE 1024 * 512	//for subscribe/user task
#define MROS_PUB_STACK_SIZE 1024 * 600	//for publish/user task
#define MROS_TASK_STACK_SIZE 1024 * 8	//for mros task
#else
#define MROS_USR2_STACK_SIZE 1024 * 1	//for user task2
#define MROS_USR1_STACK_SIZE 1024 * 1 	//for user task1
#define MROS_TASK_STACK_SIZE 1024 * 2	//for mros task
#endif
#endif	/*MROS_TASK_STACK_SIZE*/

#ifndef CYC
#define MROS_LOOP_RATE 100
#define CYC
#endif	/*CYC*/

#ifndef LOOP_REF
#define LOOP_REF		ULONG_C(1000000)	/* number of loops to evaluate speed */
#endif /* LOOP_REF */

#ifdef __cplusplus
}
#endif


#endif /* _MROS_OS_CONFIG_H_ */
