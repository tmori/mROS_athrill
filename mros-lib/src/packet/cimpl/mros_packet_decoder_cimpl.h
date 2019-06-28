#ifndef _MROS_PACKET_DECODER_CIMPL_H_
#define _MROS_PACKET_DECODER_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_packet_cimpl.h"

extern mRosReturnType mros_packet_decoder_init(void);


/************************************************
 * XML RPC PACKET
 ************************************************/
/*
 * XML request
 */
extern mros_boolean mros_xmlpacket_has_request_end(mRosPacketType *packet);
/*
 * XML response
 */
extern mros_boolean mros_xmlpacket_has_response_end(mRosPacketType *packet);

//MASTER
/*
 * ReigsterPublish response
 */
extern mRosReturnType mros_xmlpacket_pubres_result(mRosPacketType *packet);

/*
 * ReigsterSubscribe response
 */
extern mRosReturnType mros_xmlpacket_subres_result(mRosPacketType *packet);
extern mRosPtrType mros_xmlpacket_subres_get_first_uri(mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port);
extern mRosPtrType mros_xmlpacket_subres_get_next_uri(mRosPtrType ptr, mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port);


//SLAVE
extern mRosPacketDataType mros_xmlpacket_slave_request_get_method(mRosPacketType *packet);

/*
 * RequestTopic request
 */
extern mRosReturnType mros_xmlpacket_slave_reqtopic_get_topic_name(mRosPacketType *packet, char* topic_name, mros_uint32 len);

/*
 * RequestTopic response
 */
extern mRosReturnType mros_xmlpacket_reqtopicres_result(mRosPacketType *packet);
extern mRosPtrType mros_xmlpacket_reqtopicres_get_first_uri(mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port);
extern mRosPtrType mros_xmlpacket_reqtopicres_get_next_uri(mRosPtrType ptr, mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port);

/****************************************************
 * TCPROS
 ****************************************************/
extern mRosReturnType mros_tcprospacket_get_body_size(mRosPacketType *packet, mRosSizeType *len);
typedef struct {
	char *callerid;
	char *tcp_nodely;
	char *topic;
	char* type;
	char *md5sum;
} mRosTcpRosPacketType;
extern mRosReturnType mros_tcprospacket_decode(mRosPacketType *packet, mRosTcpRosPacketType *decoded_packet);


/****************************************************
 * TOPIC DATA
 ****************************************************/
extern mRosReturnType mros_topicpacket_get_body_size(mRosPacketType *packet, mRosSizeType *len);


#if 0
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
#endif

#ifdef __cplusplus
}
#endif

#endif /* _MROS_PACKET_DECODER_CIMPL_H_ */
