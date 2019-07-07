#include "mros_types.h"
#include "mros_memory.h"
#include "mros_config.h"


/*******************************************************
 * START: Inner Publish Config
 *******************************************************/

#define ROS_INNER_TOPIC_PUBLISHER_CONFIG_NUM			3U
#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL1_SIZE		16U
#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL1_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_inner_topic_publisher_mempool1, ROS_INNER_TOPIC_PUBLISHER_MEMPOOL1_QUELEN, ROS_INNER_TOPIC_PUBLISHER_MEMPOOL1_SIZE);

#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL2_SIZE		32U
#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL2_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_inner_topic_publisher_mempool2, ROS_INNER_TOPIC_PUBLISHER_MEMPOOL2_QUELEN, ROS_INNER_TOPIC_PUBLISHER_MEMPOOL2_SIZE);

#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL3_SIZE		64U
#define ROS_INNER_TOPIC_PUBLISHER_MEMPOOL3_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_inner_topic_publisher_mempool3, ROS_INNER_TOPIC_PUBLISHER_MEMPOOL3_QUELEN, ROS_INNER_TOPIC_PUBLISHER_MEMPOOL3_SIZE);

static mRosMemoryConfigType *ros_inner_topic_publisher_config[ROS_INNER_TOPIC_PUBLISHER_CONFIG_NUM] = {
		&ros_inner_topic_publisher_mempool1_config,
		&ros_inner_topic_publisher_mempool2_config,
		&ros_inner_topic_publisher_mempool3_config,
};
MROS_MEMORY_CONFIG_DECLARE_MANAGER(ros_inner_topic_publisher_mempool, ROS_INNER_TOPIC_PUBLISHER_CONFIG_NUM);
/*******************************************************
 * END
 *******************************************************/


/*******************************************************
 * START: Outer Publish Config
 *******************************************************/

#define ROS_OUTER_TOPIC_PUBLISHER_CONFIG_NUM			3U
#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL1_SIZE		16U
#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL1_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_outer_topic_publisher_mempool1, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL1_QUELEN, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL1_SIZE);

#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL2_SIZE		32U
#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL2_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_outer_topic_publisher_mempool2, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL2_QUELEN, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL2_SIZE);

#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL3_SIZE		64U
#define ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL3_QUELEN		1U
MROS_MEMORY_CONFIG_DECLARE_ENTRY(ros_outer_topic_publisher_mempool3, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL3_QUELEN, ROS_OUTER_TOPIC_PUBLISHER_MEMPOOL3_SIZE);

static mRosMemoryConfigType *ros_outer_topic_publisher_config[ROS_OUTER_TOPIC_PUBLISHER_CONFIG_NUM] = {
		&ros_outer_topic_publisher_mempool1_config,
		&ros_outer_topic_publisher_mempool2_config,
		&ros_outer_topic_publisher_mempool3_config,
};
MROS_MEMORY_CONFIG_DECLARE_MANAGER(ros_outer_topic_publisher_mempool, ROS_OUTER_TOPIC_PUBLISHER_CONFIG_NUM);
/*******************************************************
 * END
 *******************************************************/


void mros_config_init(void)
{
	mRosReturnType ret;

	ret = mros_mem_init(ROS_INNER_TOPIC_PUBLISHER_CONFIG_NUM, ros_inner_topic_publisher_config, &ros_inner_topic_publisher_mempool);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	ret = mros_mem_init(ROS_OUTER_TOPIC_PUBLISHER_CONFIG_NUM, ros_outer_topic_publisher_config, &ros_outer_topic_publisher_mempool);
	if (ret != MROS_E_OK) {
		ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		return;
	}
	return;
}
