#ifndef _MROS_PACKET_CIMPL_H_
#define _MROS_PACKET_CIMPL_H_

#include "mros_types.h"
#include "mros_config.h"

typedef enum {
	MROS_PACKET_DATA_REGISTER_PUBLISHER = 0,
	MROS_PACKET_DATA_REGISTER_SUBSCRIBER,
	MROS_PACKET_DATA_REQUEST_TOPIC,
	MROS_PACKET_DATA_TCPROS_PUB,
	MROS_PACKET_DATA_TCPROS_SUB,
	MROS_PACKET_DATA_TOPIC,
	MROS_PACKET_DATA_NUM,
} mRosPacketDataType;

typedef struct {
	mRosSizeType						total_size;
	mRosSizeType						data_size;
	char							 	data[MROS_PACKET_MAXSIZE];
} mRosPacketType;

/*************************************
 * Encoder
 *************************************/
#define MROS_ENCODE_ARGS_MAX	5
typedef struct {
	mRosPacketDataType type;
	mRosSizeType	args_char;
	const char* 	argv[MROS_ENCODE_ARGS_MAX];
	mRosSizeType	args_int;
	mros_uint32		argi[MROS_ENCODE_ARGS_MAX];
} mRosEncodeArgType;

extern mRosReturnType mros_packet_encode(mRosEncodeArgType *arg, mRosPacketType *packet);

#endif /* _MROS_PACKET_CIMPL_H_ */
