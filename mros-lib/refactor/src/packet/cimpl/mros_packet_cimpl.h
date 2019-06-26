#ifndef _MROS_PACKET_CIMPL_H_
#define _MROS_PACKET_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_types.h"
#include "mros_config.h"

typedef enum {
	MROS_PACKET_DATA_REGISTER_PUBLISHER_REQ = 0,
	MROS_PACKET_DATA_REGISTER_SUBSCRIBER_REQ,
	MROS_PACKET_DATA_REQUEST_TOPIC_REQ,
	MROS_PACKET_DATA_REQUEST_TOPIC_RES,
	MROS_PACKET_DATA_TCPROS_PUB_REQ,
	MROS_PACKET_DATA_TCPROS_PUB_RES,
	MROS_PACKET_DATA_TOPIC,
	MROS_PACKET_DATA_NUM,
} mRosPacketDataType;

typedef struct {
	mRosSizeType						total_size;
	mRosSizeType						data_size;
	char							 	*data;
} mRosPacketType;

#ifdef __cplusplus
}
#endif

#endif /* _MROS_PACKET_CIMPL_H_ */
