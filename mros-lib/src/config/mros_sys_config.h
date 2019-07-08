#ifndef _MROS_SYS_CONFIG_H_
#define _MROS_SYS_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_usr_config.h"
#include "mros_os_config.h"
#include "mros_packet_config.h"



/**************************************
 * PROTOCOL
 **************************************/
/*
 * portno of master
 */
#define MROS_MASTER_PORT_NO						11311
/*
 * ipaddr of master
 */
#define MROS_MASTER_IPADDR						"0.0.0.0"

#define MROS_NODE_IPADDR						"127.0.0.1"

/*
 * portno of slave
 */
#define MROS_SLAVE_PORT_NO						11411

/*
 * portno of pub
 */
#define MROS_PUBLISHER_PORT_NO					11511

#define MROS_URI_SLAVE							"http://127.0.0.1:11411"

#define MROS_TOPIC_TCP_CLIENT_MAX_NUM			( \
			( MROS_PUB_TOPIC_CONNECTOR_MAX_NUM > MROS_SUB_TOPIC_CONNECTOR_MAX_NUM) ? \
			  MROS_PUB_TOPIC_CONNECTOR_MAX_NUM : \
			  MROS_SUB_TOPIC_CONNECTOR_MAX_NUM \
	)


#define MROS_OUTER_CONNECTOR_QUEUE_MAXLEN		1


/*****************************************
 * EXCLUSIVE AREA
 *****************************************/

#define MROS_GIANT_EXCLUSIVE_AREA_PRIORITY		MROS_USR_TASK_PRI


/*****************************************
 * TASK CYCLE
 *****************************************/
#define MROS_SLAVE_TIMEOUT			100
#define MROS_PUBLISH_TIMEOUT		50


extern void mros_sys_config_init(void);
extern void usr_task_activation(void);

#ifdef __cplusplus
}
#endif

#endif /* _MROS_SYS_CONFIG_H_ */

