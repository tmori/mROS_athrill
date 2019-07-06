#ifndef _MROS_OS_TARGET_H_
#define _MROS_OS_TARGET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>
#include <t_syslog.h>
#include "mros_types.h"

typedef ID	mRosTaskIdType;
typedef PRI	mRosTaskPriorityType;

#define MROS_TASK_MAX_PRIORITY 	TMAX_TPRI

#define MROS_LOG_EMRG		LOG_EMERG
#define MROS_LOG_ALERT		LOG_ALERT
#define MROS_LOG_CRIT		LOG_CRIT
#define MROS_LOG_ERROR		LOG_ERROR
#define MROS_LOG_WARNING	LOG_WARNING
#define MROS_LOG_NOTICE		LOG_NOTICE
#define MROS_LOG_INFO		LOG_INFO
#define MROS_LOG_DEBUG		LOG_DEBUG

#define ROS_DEBUG(...) 		syslog(LOG_DEBUG, __VA_ARGS__)
#define ROS_INFO(...) 		syslog(LOG_NOTICE, __VA_ARGS__)
#define ROS_WARN(...) 		syslog(LOG_WARNING, __VA_ARGS__)
#define ROS_ERROR(...) 		syslog(LOG_ERROR, __VA_ARGS__)
#define ROS_FATAL(...) 		syslog(LOG_EMERG, __VA_ARGS__)



#ifdef __cplusplus
}
#endif


#endif /* _MROS_OS_TARGET_H_ */
