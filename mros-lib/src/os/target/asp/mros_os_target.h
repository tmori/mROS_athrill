#ifndef _MROS_OS_TARGET_H_
#define _MROS_OS_TARGET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>
#include "mros_types.h"

typedef ID	mRosTaskIdType;
typedef PRI	mRosTaskPriorityType;

#define MROS_TASK_MAX_PRIORITY 	TMAX_TPRI

#ifdef __cplusplus
}
#endif


#endif /* _MROS_OS_TARGET_H_ */
