#ifndef _MROS_OS_CONFIG_H_
#define _MROS_OS_CONFIG_H_

#include "kernel.h"

extern void main_task();
extern void sub_task();
extern void pub_task();
extern void xml_slv_task();
extern void xml_mas_task();
extern void usr_task1();
extern void usr_task2();

extern void sus_all();
extern void rsm_all();

extern void cyclic_handler(intptr_t exinf);


#endif /* _MROS_OS_CONFIG_H_ */
