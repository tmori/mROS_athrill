#ifndef _MROS_CONFIG_H_
#define _MROS_CONFIG_H_

/**************************************
 * TOPIC
 **************************************/

/*
 * num of max topics
 */
#define MROS_TOPIC_MAX_NUM						10U


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

/**************************************
 * PROTOCOL
 **************************************/

/*
 * portno of master
 */
#define MROS_MASTER_PORT_NO						1131
/*
 * ipaddr of master
 */
#define MROS_MASTER_IPADDR						"0.0.0.0"

#define MROS_NODE_IPADDR						"0.0.0.0"

/*
 * portno of slave
 */
#define MROS_SLAVE_PORT_NO						1141

/*
 * portno of pub
 */
#define MROS_PUBLISHER_PORT_NO					1151

#define MROS_IPADDR								"0.0.0.0"
#define MROS_URI_SLAVE							"http://0.0.0.0/1141"


#define MROS_TOPIC_TCP_CLIENT_MAX_NUM			10
#define MROS_TOPIC_NAME_MAXLEN					128

/**************************************
 * PACKET
 **************************************/
#define MROS_PACKET_MAXSIZE_REQ_REGISTER_PUBLISHER		512
#define MROS_PACKET_MAXSIZE_RES_REGISTER_PUBLISHER		512
#define MROS_PACKET_MAXSIZE_REQ_REGISTER_SUBSCRIBER		512
#define MROS_PACKET_MAXSIZE_RES_REGISTER_SUBSCRIBER		512
#define MROS_PACKET_MAXSIZE_REQ_REQUEST_TOPIC			512
#define MROS_PACKET_MAXSIZE_RES_REQUEST_TOPIC			512


#define MROS_PACKET_MAXSIZE_REQ_TCPROS					512
#define MROS_PACKET_MAXSIZE_RES_TCPROS					512

#define MROS_OUTER_CONNECTOR_QUEUE_MAXLEN				1


#define MROS_TOPIC_RAWDATA_HEADER_SIZE					8

#endif /* _MROS_CONFIG_H_ */


/*****************************************
 * EXCLUSIVE AREA
 *****************************************/

#define MROS_GIANT_EXCLUSIVE_AREA_PRIORITY		MROS_TASK_MAX_PRIORITY

