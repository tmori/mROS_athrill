#ifndef _MROS_PACKET_ENCODER_CIMPL_H_
#define _MROS_PACKET_ENCODER_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_packet_cimpl.h"

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

extern mRosReturnType mros_packet_encoder_init(void);
extern mRosReturnType mros_packet_encode(mRosEncodeArgType *arg, mRosPacketType *packet);

//TODO
extern mRosReturnType mros_packet_encode_topic_data(mRosPacketType *packet, const char* data, mros_uint32 len);
extern mRosReturnType mros_packet_encode_request_topic_res(mRosPacketType *packet, const char* ipaddr, mros_int32 port);

#ifdef __cplusplus
}
#endif

#endif /* _MROS_PACKET_ENCODER_CIMPL_H_ */
