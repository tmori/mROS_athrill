#ifndef _MROS_CONFIG_H_
#define _MROS_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

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


#define MROS_TOPIC_TCP_CLIENT_MAX_NUM			10

/**************************************
 * PACKET
 **************************************/
#define MROS_PACKET_MAXSIZE_REQ_REGISTER_PUBLISHER		1024
#define MROS_PACKET_MAXSIZE_RES_REGISTER_PUBLISHER		1024
#define MROS_PACKET_MAXSIZE_REQ_REGISTER_SUBSCRIBER		1024
#define MROS_PACKET_MAXSIZE_RES_REGISTER_SUBSCRIBER		1024
#define MROS_PACKET_MAXSIZE_REQ_REQUEST_TOPIC			1024
#define MROS_PACKET_MAXSIZE_RES_REQUEST_TOPIC			1024


#define MROS_PACKET_MAXSIZE_REQ_TCPROS					512
#define MROS_PACKET_MAXSIZE_RES_TCPROS					512

#define MROS_OUTER_CONNECTOR_QUEUE_MAXLEN				1


#define MROS_TOPIC_RAWDATA_HEADER_SIZE					8
#define MROS_TCPROS_RAWDATA_HEADER_SIZE					4



/*****************************************
 * EXCLUSIVE AREA
 *****************************************/

#define MROS_GIANT_EXCLUSIVE_AREA_PRIORITY		MROS_TASK_MAX_PRIORITY


#define MROS_SLAVE_TIMEOUT			100
#define MROS_PUBLISH_TIMEOUT		10

/****************************************
 * kernel cfg
 ****************************************/
#ifndef MROS_USR_TASK_PRI
#define MAIN_TASK_PRI 			7
#define MROS_USR_TASK_PRI  		8
#define MROS_TASK_PRI  			6
#endif /* ROS_USR_TASK_PRI */

#ifndef TASK_PORTID
#define	TASK_PORTID		1			/* serial port ID for something typing */
#endif /* TASK_PORTID */

#ifndef MROS_TASK_STACK_SIZE
#define MROS_SUB_STACK_SIZE 1024 * 512	//for subscribe/user task
#define MROS_PUB_STACK_SIZE 1024 * 600	//for publish/user task
#define MROS_TASK_STACK_SIZE 1024 * 8	//for mros task
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

#endif /* _MROS_CONFIG_H_ */

