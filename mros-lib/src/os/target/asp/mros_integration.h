#ifndef _MROS_INTEGRATION_H_
#define _MROS_INTEGRATION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_types.h"
#include "mros_memory.h"

extern mRosMemoryManagerType ros_inner_topic_publisher_mempool;
extern mRosMemoryManagerType ros_outer_topic_publisher_mempool;

extern void mros_config_init(void);


extern void mros_topic_callback(mRosFuncIdType func_id, const char *data);
extern void usr_task1(void);
extern void usr_task2(void);
extern void usr_task_activation(void);


#ifdef __cplusplus
}
#endif


#endif /* _MROS_INTEGRATION_H_ */
