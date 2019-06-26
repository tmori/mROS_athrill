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


/************************************************
 * MASTER PACKET
 ************************************************/
/*
 * XML response
 */
extern mros_boolean mros_packet_has_response_end(mRosPacketType *packet);

/*
 * ReigsterPublish response
 */
extern mRosReturnType mros_packet_get_regpub_result(mRosPacketType *packet);


/*
 * ReigsterSubscribe response
 */
extern mRosReturnType mros_packet_get_regsub_result(mRosPacketType *packet);
extern mRosPtrType mros_packet_get_regsub_first_uri(mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port);
extern mRosPtrType mros_packet_get_regsub_next_uri(mRosPtrType ptr, mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port);


/************************************************
 * SLAVE PACKET
 ************************************************/
extern mros_boolean mros_packet_has_request_end(mRosPacketType *packet);
extern mRosPacketDataType mros_packet_get_method(mRosPacketType *packet);

/*
 * RequestTopic request
 */
extern mRosReturnType mros_packet_get_topic_name(mRosPacketType *packet, char* topic_name, mros_uint32 len);

/*
 * RequestTopic response
 */
extern mRosReturnType mros_packet_get_reqtopic_result(mRosPacketType *packet);
extern mRosPtrType mros_packet_get_reqtopic_first_uri(mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port);
extern mRosPtrType mros_packet_get_reqtopic_next_uri(mRosPtrType ptr, mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port);

/*
 * TOPIC DATA
 */
extern mRosReturnType mros_packet_get_body_size(mRosPacketType *packet, mRosSizeType *len);

#ifdef __cplusplus
}
#endif

#endif /* _MROS_PACKET_DECODER_CIMPL_H_ */
