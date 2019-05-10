#include "mros_packet_decoder.h"
#include <string.h>
#include <stdlib.h>

using namespace mros::packet;
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

mRosReturnType mRosPacketDecoder::decode_port(mros_uint32 &port, mRosPacketType &packet)
{
	char val[PORT_MAX_STR_LEN];

	//search HERE
	//        |
	//        V
	//"http://xxx.xxx.xx:8080/"
	const char* head = find_string_after((const char *)&packet.data->data.memp[0], "http://");
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

	port = strtol(val, NULL, 10);
	return MROS_E_OK;
}
#if 0

mRosReturnType mRosPacketDecoder::decode_port(std::string &port, mRosPacketType &packet)
{
	return MROS_E_OK;
}
mRosReturnType mRosPacketDecoder::decode_ip(std::string &ip, mRosPacketType &packet)
{
	return MROS_E_OK;
}

mRosReturnType mRosPacketDecoder::decode_method(std::string &method, mRosPacketType &packet)
{
	return MROS_E_OK;
}
mRosReturnType mRosPacketDecoder::decode_topic_type(std::string &topic_type, mRosPacketType &packet)
{
	return MROS_E_OK;
}
mRosReturnType mRosPacketDecoder::decode_topic_name(std::string &topic_name, mRosPacketType &packet)
{
	return MROS_E_OK;
}
mRosReturnType mRosPacketDecoder::decode_caller_id(std::string &caller_id, mRosPacketType &packet)
{
	return MROS_E_OK;
}
mRosReturnType mRosPacketDecoder::decode_message_definition(std::string &msgdef, mRosPacketType &packet)
{
	return MROS_E_OK;
}
mRosReturnType mRosPacketDecoder::decode_fptr(std::string &fptr, mRosPacketType &packet)
{
	return MROS_E_OK;
}
mRosReturnType mRosPacketDecoder::decode_req_topic_name(std::string &topic_name, mRosPacketType &packet)
{
	return MROS_E_OK;
}
#endif
