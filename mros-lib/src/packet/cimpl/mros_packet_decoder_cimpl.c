#include "mros_packet_decoder_cimpl.h"
#include "mros_packet_fmt_xml.h"
#include "mros_packet_fmt_http.h"
#include <string.h>
#include <stdlib.h>

static mros_int32 mros_packet_xmlrpc_req_end_str_len = 0;
static mros_int32 mros_packet_xmlrpc_res_end_str_len = 0;

mRosReturnType mros_packet_decoder_init(void)
{
	mros_packet_xmlrpc_req_end_str_len = strlen(MROS_PACKET_XMLRPC_REQ_END_STR) + 1;
	mros_packet_xmlrpc_res_end_str_len = strlen(MROS_PACKET_XMLRPC_RES_END_STR) + 1;
	return MROS_E_OK;
}


static char *find_string_after(const char* string1, const char* string2)
{
	char* str = strstr(string1, string2);
	if (str == NULL) {
		return NULL;
	}
	str += strlen(string2);
	return str;
}
#define PORT_MAX_STR_LEN	6U /* 65536 */

static mRosReturnType mros_packet_decode_port_integer(mros_uint32 *port, mRosPacketType *packet)
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
	mros_int32 off;
	if (packet->data_size <= mros_packet_xmlrpc_req_end_str_len) {
		return MROS_FALSE;
	}
	off = (mros_int32)packet->data_size - (mros_int32)mros_packet_xmlrpc_req_end_str_len;
	while (off > 0) {
		if (strncmp(&packet->data[off], MROS_PACKET_XMLRPC_REQ_END_STR, mros_packet_xmlrpc_req_end_str_len) == 0) {
			return MROS_TRUE;
		}
		off--;
	}
	return MROS_FALSE;
}

/*
 * XML response
 */
mros_boolean mros_xmlpacket_has_response_end(mRosPacketType *packet)
{
	mros_int32 off;
	if (packet->data_size <= mros_packet_xmlrpc_res_end_str_len) {
		return MROS_FALSE;
	}
	off = (mros_int32)packet->data_size - (mros_int32)mros_packet_xmlrpc_res_end_str_len;
	while (off > 0) {
		if (strncmp(&packet->data[off], MROS_PACKET_XMLRPC_RES_END_STR, mros_packet_xmlrpc_res_end_str_len) == 0) {
			break;
		}
		off--;
	}
	return MROS_FALSE;
}

static mRosReturnType mros_xmlpacket_result(mRosPacketType *packet)
{
	//search HERE
	//        |
	//        V
	//    HTTP/1.1 200 OK
	const char* head = find_string_after((const char *)&packet->data[0], "HTTP/");
	if (head == NULL) {
		return MROS_E_INVAL;
	}
	//    search HERE
	//            |
	//            V
	//    HTTP/1.1 200 OK
	head = find_string_after(head, " ");
	if (head == NULL) {
		return MROS_E_INVAL;
	}
	//        search HERE
	//                |
	//                V
	//    HTTP/1.1 200 OK
	const char* tail = strstr(head, " ");
	mros_uint32 len = (tail - head) + 1;
	if (len != MROS_PACKET_HTT_OK_CODE_LEN) {
		return MROS_E_INVAL;
	}
	if (strncmp(head, MROS_PACKET_HTT_OK_CODE, MROS_PACKET_HTT_OK_CODE_LEN) != 0) {
		return MROS_E_INVAL;
	}
	return MROS_E_OK;
}

//MASTER
/*
 * ReigsterPublish response
 */
mRosReturnType mros_xmlpacket_pubres_result(mRosPacketType *packet)
{
	return mros_xmlpacket_result(packet);
}

/*
 * ReigsterSubscribe response
 */
mRosReturnType mros_xmlpacket_subres_result(mRosPacketType *packet)
{
	return mros_xmlpacket_result(packet);
}

mRosPtrType mros_xmlpacket_subres_get_first_uri(mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port)
{
	//TODO
	return MROS_E_OK;
}

mRosPtrType mros_xmlpacket_subres_get_next_uri(mRosPtrType ptr, mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port)
{
	//TODO
	return NULL;
}


static mRosReturnType mros_xmlpacket_get_member_info(const char*p, mRosPacketMemberInfoType *infop)
{
	infop->res.head = find_string_after(p, infop->req.start_key);
	if (infop->res.head == NULL) {
		return MROS_E_INVAL;
	}

	infop->res.tail = strstr(infop->res.head, "<");
	if (infop->res.tail == NULL) {
		return MROS_E_INVAL;
	}
	infop->res.len = (infop->res.tail - infop->res.head) + 1;
	return MROS_E_OK;
}

//SLAVE
static mRosPacketDataType mros_xmlpacket_slave_request_get_method(mRosPacketType *packet, mRosPacketMemberInfoType *minfop)
{
	mRosReturnType ret;
	mRosSizeType len = strlen("requestTopic");

	//"<methodName>requestTopic</methodName>"
	minfop->req.start_key = "<methodName>";
	minfop->req.end_key = "<";

	ret = mros_xmlpacket_get_member_info(packet->data, minfop);
	if (ret != MROS_E_OK) {
		return MROS_PACKET_DATA_INVALID;
	}
	if (len != minfop->res.len) {
		return MROS_PACKET_DATA_INVALID;
	}
	if (strncmp(minfop->res.head, "requestTopic", len) == 0) {
		return MROS_PACKET_DATA_REQUEST_TOPIC_REQ;
	}

	return MROS_PACKET_DATA_INVALID;
}
#ifdef ROS_INDIGO
#define REQTOPIC_VALUE_TAG_START "<value>"
#define REQTOPIC_VALUE_TAG_END "</value>"
#else
#define REQTOPIC_VALUE_TAG_START "<value><string>"
#define REQTOPIC_VALUE_TAG_END "</string></value>"
#endif

static mRosReturnType mros_xmlpacket_request_topic_req_decode(mRosPacketType *packet, mRosPacketDecodedRequestType *decoded_infop)
{
	mRosReturnType ret;

	decoded_infop->request.topic.node_name.req.start_key = REQTOPIC_VALUE_TAG_START;
	decoded_infop->request.topic.node_name.req.end_key = "<";
	ret = mros_xmlpacket_get_member_info(decoded_infop->method.res.tail, &decoded_infop->request.topic.node_name);
	if (ret != MROS_E_OK) {
		return MROS_E_INVAL;
	}
	decoded_infop->request.topic.topic_name.req.start_key = REQTOPIC_VALUE_TAG_START;
	decoded_infop->request.topic.topic_name.req.end_key = "<";
	ret = mros_xmlpacket_get_member_info(decoded_infop->request.topic.topic_name.res.tail, &decoded_infop->request.topic.topic_name);
	if (ret != MROS_E_OK) {
		return MROS_E_INVAL;
	}

	return MROS_E_OK;
}

mRosPacketDataType mros_xmlpacket_slave_request_decode(mRosPacketType *packet, mRosPacketDecodedRequestType *decoded_infop)
{
	mRosReturnType ret = MROS_E_INVAL;
	decoded_infop->packet_type = mros_xmlpacket_slave_request_get_method(packet, &decoded_infop->method);
	switch (decoded_infop->packet_type) {
	case MROS_PACKET_DATA_REQUEST_TOPIC_REQ:
		ret = mros_xmlpacket_request_topic_req_decode(packet, decoded_infop);
		break;
	default:
		break;
	}
	if (ret != MROS_E_OK) {
		return MROS_PACKET_DATA_INVALID;
	}
	return decoded_infop->packet_type;
}


/*
 * RequestTopic request
 */
mRosReturnType mros_xmlpacket_slave_reqtopic_get_topic_name(mRosPacketType *packet, char* topic_name, mros_uint32 len)
{
	//TODO
	return MROS_E_OK;
}


/*
 * RequestTopic response
 */
mRosReturnType mros_xmlpacket_reqtopicres_result(mRosPacketType *packet)
{
	return mros_xmlpacket_result(packet);
}

mRosPtrType mros_xmlpacket_reqtopicres_get_first_uri(mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port)
{
	//TODO
	return MROS_E_OK;
}

mRosPtrType mros_xmlpacket_reqtopicres_get_next_uri(mRosPtrType ptr, mRosPacketType *packet, mros_uint32 *ipaddr, mros_int32 *port)
{
	//TODO
	return NULL;
}


/****************************************************
 * TCPROS
 ****************************************************/
mRosReturnType mros_tcprospacket_get_body_size(mRosPacketType *packet, mRosSizeType *len)
{
	*len = *((mRosSizeType*)&packet->data[0]); //TODO INDIGO
	return MROS_E_OK;
}

mRosReturnType mros_tcprospacket_decode(mRosPacketType *packet, mRosTcpRosPacketType *decoded_packet)
{
	mros_uint32 len;
	mros_uint32 off = 4;
	mros_uint32 memlen;
	mros_uint32 entrylen;

	len = *((mRosSizeType*)&packet->data[off]);
	off += 4;

	decoded_packet->callerid = NULL;
	decoded_packet->md5sum = NULL;
	decoded_packet->tcp_nodely = NULL;
	decoded_packet->topic = NULL;
	decoded_packet->type = NULL;


	while (off < len) {
		entrylen = *((mRosSizeType*)&packet->data[off]);
		off += 4;
		if (off >= len) {
			break;
		}

		if (strncmp(&packet->data[off], "callerid=", memlen) == 0) {
			memlen = strlen("callerid=");
			decoded_packet->callerid = (char*)&packet->data[off + memlen];
		}
		else if (strncmp(&packet->data[off], "md5sum=", memlen) == 0) {
			memlen = strlen("md5sum=");
			decoded_packet->md5sum = (char*)&packet->data[off + memlen];
		}
		else if (strncmp(&packet->data[off], "tcp_nodely=", memlen) == 0) {
			memlen = strlen("tcp_nodely=");
			decoded_packet->tcp_nodely = (char*)&packet->data[off + memlen];
		}
		else if (strncmp(&packet->data[off], "topic=", memlen) == 0) {
			memlen = strlen("topic=");
			decoded_packet->topic = (char*)&packet->data[off + memlen];
		}
		else if (strncmp(&packet->data[off], "type=", memlen) == 0) {
			memlen = strlen("type=");
			decoded_packet->type = (char*)&packet->data[off + memlen];
		}
		off += entrylen;
	}


	return MROS_E_OK;
}


/****************************************************
 * TOPIC DATA
 ****************************************************/
mRosReturnType mros_topicpacket_get_body_size(mRosPacketType *packet, mRosSizeType *len)
{
	*len = *((mRosSizeType*)&packet->data[4]);//TODO INDIGO
	return MROS_E_OK;
}

