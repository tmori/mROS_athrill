#include "mros_packet_decoder_cimpl.h"
#include <string.h>
#include <stdlib.h>

static const char *find_string_after(const char* string1, const char* string2)
{
	const char* str = strstr(string1, string2);
	if (str == NULL) {
		return NULL;
	}
	str += strlen(string2);
	return str;
}
#define PORT_MAX_STR_LEN	6U /* 65536 */

mRosReturnType mros_packet_decode_port_integer(mros_uint32 *port, mRosPacketType *packet)
{
	char val[PORT_MAX_STR_LEN];

	//search HERE
	//        |
	//        V
	//"http://xxx.xxx.xx:8080/"
	const char* head = find_string_after((const char *)&packet->data[0], "http://");
	if (head == NULL) {
		return MROS_E_INVAL;
	}

	//           search HERE
	//                   |
	//                   V
	//"http://xxx.xxx.xx:8080/"
	head = find_string_after(head, ":");
	if (head == NULL) {
		return MROS_E_INVAL;
	}

	//               search HERE
	//                       |
	//                       V
	//"http://xxx.xxx.xx:8080/"
	const char* tail = strstr(head, "/");
	mros_uint32 len = (tail - head) + 1;
	if (len > PORT_MAX_STR_LEN) {
		return MROS_E_INVAL;
	}

	memcpy(&val[0], head, (len - 1));
	val[len - 1] = '\0';

	*port = strtol(val, NULL, 10);
	return MROS_E_OK;
}


/************************************************
 * XML RPC PACKET
 ************************************************/
/*
 * XML request
 */
mros_boolean mros_xmlpacket_has_request_end(mRosPacketType *packet)
{
	//TODO
	return MROS_E_OK;
}

/*
 * XML response
 */
mros_boolean mros_xmlpacket_has_response_end(mRosPacketType *packet)
{
	//TODO
	return MROS_E_OK;
}


//MASTER
/*
 * ReigsterPublish response
 */
mRosReturnType mros_xmlpacket_pubres_result(mRosPacketType *packet)
{
	//TODO
	return MROS_E_OK;
}


/*
 * ReigsterSubscribe response
 */
mRosReturnType mros_xmlpacket_subres_result(mRosPacketType *packet)
{
	//TODO
	return MROS_E_OK;
}

mRosPtrType mros_xmlpacket_subres_get_first_uri(mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port)
{
	//TODO
	return MROS_E_OK;
}

mRosPtrType mros_xmlpacket_subres_get_next_uri(mRosPtrType ptr, mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port)
{
	//TODO
	return MROS_E_OK;
}



//SLAVE
mRosPacketDataType mros_xmlpacket_slave_request_get_method(mRosPacketType *packet)
{
	//TODO
	return MROS_E_OK;
}


/*
 * RequestTopic request
 */
mRosReturnType mros_xmlpacket_slave_reqtopic_get_topic_name(mRosPacketType *packet, char** topic_name, mros_uint32 len)
{
	//TODO
	return MROS_E_OK;
}


/*
 * RequestTopic response
 */
mRosReturnType mros_xmlpacket_reqtopicres_result(mRosPacketType *packet)
{
	//TODO
	return MROS_E_OK;
}

mRosPtrType mros_xmlpacket_reqtopicres_get_first_uri(mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port)
{
	//TODO
	return MROS_E_OK;
}

mRosPtrType mros_xmlpacket_reqtopicres_get_next_uri(mRosPtrType ptr, mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port)
{
	//TODO
	return MROS_E_OK;
}


/****************************************************
 * TCPROS
 ****************************************************/
mRosReturnType mros_tcprospacket_get_body_size(mRosPacketType *packet, mRosSizeType *len)
{
	//TODO
	return MROS_E_OK;
}

mRosReturnType mros_tcprospacket_get_topic_name(mRosPacketType *packet, char** topic_name, mros_uint32 len)
{
	//TODO
	return MROS_E_OK;
}


/****************************************************
 * TOPIC DATA
 ****************************************************/
mRosReturnType mros_topicpacket_get_body_size(mRosPacketType *packet, mRosSizeType *len)
{
	//TODO
	return MROS_E_OK;
}


#if 0
mRosReturnType mros_packet_decode_port(char *port, mRosPacketType *packet)
{
	return MROS_E_OK;
}
mRosReturnType mros_packet_decode_ip(char *ip, mRosPacketType *packet)
{
	return MROS_E_OK;
}

mRosReturnType mros_packet_decode_method(char *method, mRosPacketType *packet)
{
	return MROS_E_OK;
}
mRosReturnType mros_packet_decode_topic_type(char *topic_type, mRosPacketType *packet)
{
	return MROS_E_OK;
}
mRosReturnType mros_packet_decode_topic_name(char *topic_name, mRosPacketType *packet)
{
	return MROS_E_OK;
}
mRosReturnType mros_packet_decode_caller_id(char *caller_id, mRosPacketType *packet)
{
	return MROS_E_OK;
}
mRosReturnType mros_packet_decode_message_definition(char* msgdef, mRosPacketType *packet)
{
	return MROS_E_OK;
}
mRosReturnType mros_packet_decode_fptr(char* fptr, mRosPacketType *packet)
{
	return MROS_E_OK;
}
mRosReturnType mros_packet_decode_req_topic_name(char* topic_name, mRosPacketType *packet)
{
	return MROS_E_OK;
}
#endif
