#ifndef _MROS_OS_TARGET_H_
#define _MROS_OS_TARGET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_types.h"

typedef mros_uint32	mRosTaskIdType;
typedef mros_uint32	mRosTaskPriorityType;

#define TMAX_TPRI 10 //TODO include os.h
#define MROS_TASK_MAX_PRIORITY 	TMAX_TPRI

#ifdef __cplusplus
}
#endif


#endif /* _MROS_OS_TARGET_H_ */
