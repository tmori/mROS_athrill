#ifndef _MROS_USR_CONFIG_H_
#define _MROS_USR_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_types.h"
#include "mros_memory.h"
#include "mros_os.h"


/**************************************
 * TOPIC
 **************************************/

/*
 * num of max topics
 */
#define MROS_TOPIC_MAX_NUM						10U

#define MROS_TOPIC_NAME_MAXLEN					20U
#define MROS_TOPIC_TYPENAME_MAXLEN				20U


/**************************************
 * TOPIC CONNECTOR
 **************************************/
/*
 * num of max publish topic connectors
 */
#define MROS_PUB_TOPIC_CONNECTOR_MAX_NUM		10U

/*
 * num of max subscribe topic connectors
 */
#define MROS_SUB_TOPIC_CONNECTOR_MAX_NUM		10U



/**************************************
 * NODE
 **************************************/
/*
 * num of max nodes
 */
#define MROS_NODE_MAX_NUM						10U
#define MROS_NODE_NAME_MAXLEN					20U


/*******************************************************
 * START: Inner Publish topic data memory Config
 *******************************************************/

#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL1_SIZE			16U
#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL1_QUELEN		1U

#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL2_SIZE			32U
#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL2_QUELEN		1U

#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL3_SIZE			64U
#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL3_QUELEN		1U

#define ROS_INNER_TOPIC_PUBLISHER_CONFIG_NUM			3U
extern mRosMemoryConfigType *ros_inner_topic_publisher_config[ROS_INNER_TOPIC_PUBLISHER_CONFIG_NUM];
extern mRosMemoryManagerType ros_inner_topic_publisher_mempool;
/*******************************************************
 * END
 *******************************************************/


/*******************************************************
 * START: Outer Publish topic data memory Config
 *******************************************************/

#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL1_SIZE			16U
#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL1_QUELEN		1U

#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL2_SIZE			32U
#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL2_QUELEN		1U

#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL3_SIZE			64U
#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL3_QUELEN		1U

#define ROS_OUTER_TOPIC_PUBLISHER_CONFIG_NUM			3U
extern mRosMemoryConfigType *ros_outer_topic_publisher_config[ROS_OUTER_TOPIC_PUBLISHER_CONFIG_NUM];
extern mRosMemoryManagerType ros_outer_topic_publisher_mempool;
/*******************************************************
 * END
 *******************************************************/

/****************************************
 * USR OS TASK
 ****************************************/
#define MROS_USR_TASK_NUM			2
extern mRosTaskIdType mros_usr_task_table[MROS_USR_TASK_NUM];

#ifdef __cplusplus
}
#endif

#endif /* _MROS_USR_CONFIG_H_ */

