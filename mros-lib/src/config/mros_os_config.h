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

#ifdef __cplusplus
}
#endif


#endif /* _MROS_OS_CONFIG_H_ */
