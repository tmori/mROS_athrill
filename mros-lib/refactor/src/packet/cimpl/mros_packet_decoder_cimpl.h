#ifndef _MROS_PACKET_DECODER_CIMPL_H_
#define _MROS_PACKET_DECODER_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_packet_cimpl.h"

extern mRosReturnType mros_packet_decode_port_integer(mros_uint32 *port, mRosPacketType *packet);
extern mRosReturnType mros_packet_decode_port(char *port, mRosPacketType *packet);
extern mRosReturnType mros_packet_decode_ip(char *ip, mRosPacketType *packet);

extern mRosReturnType mros_packet_decode_method(char *method, mRosPacketType *packet);
extern mRosReturnType mros_packet_decode_topic_type(char *topic_type, mRosPacketType *packet);
extern mRosReturnType mros_packet_decode_topic_name(char *topic_name, mRosPacketType *packet);
extern mRosReturnType mros_packet_decode_caller_id(char *caller_id, mRosPacketType *packet);
extern mRosReturnType mros_packet_decode_message_definition(char* msgdef, mRosPacketType *packet);
extern mRosReturnType mros_packet_decode_fptr(char* fptr, mRosPacketType *packet);
extern mRosReturnType mros_packet_decode_req_topic_name(char* topic_name, mRosPacketType *packet);


#ifdef __cplusplus
}
#endif

#endif /* _MROS_PACKET_DECODER_CIMPL_H_ */
