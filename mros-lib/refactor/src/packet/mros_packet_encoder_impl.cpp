#include "mros_packet_encoder.h"
#include "mros_packet_fmt_xml.h"
#include "mros_packet_fmt_http.h"
#include <string.h>
#include <stdio.h>

using namespace mros::packet;

static mRosReturnType encode_register_publisher(mRosEncodeArgType &arg, mRosPacketType &packet);
static mRosReturnType encode_register_subscriber(mRosEncodeArgType &arg, mRosPacketType &packet);
static mRosReturnType encode_request_topic(mRosEncodeArgType &arg, mRosPacketType &packet);

typedef mRosReturnType (*encode_table_type) (mRosEncodeArgType&, mRosPacketType&);

static encode_table_type encode_table[MROS_PACKET_DATA_NUM] = {
		encode_register_publisher,
		encode_register_subscriber,
		encode_request_topic,
};

typedef struct {
	const char* fmt;
	mros_uint32 len;
} mRosFmtType;

static mRosFmtType mros_xml_fmt_table[MROS_PACKET_DATA_NUM];
static mRosFmtType mros_http_post_fmt;
static mRosFmtType mros_http_ok_fmt;

mRosReturnType mRosPacketEncoder::init()
{
	mros_xml_fmt_table[MROS_PACKET_DATA_REGISTER_PUBLISHER].fmt = MROS_PACKET_FMT_XML_REGISTER;
	mros_xml_fmt_table[MROS_PACKET_DATA_REGISTER_PUBLISHER].len = strlen(MROS_PACKET_FMT_XML_REGISTER) + 1;

	mros_xml_fmt_table[MROS_PACKET_DATA_REGISTER_SUBSCRIBER].fmt = MROS_PACKET_FMT_XML_REGISTER;
	mros_xml_fmt_table[MROS_PACKET_DATA_REGISTER_SUBSCRIBER].len = strlen(MROS_PACKET_FMT_XML_REGISTER) + 1;

	mros_xml_fmt_table[MROS_PACKET_DATA_REQUEST_TOPIC].fmt = MROS_PACKET_FMT_XML_REQUEST;
	mros_xml_fmt_table[MROS_PACKET_DATA_REQUEST_TOPIC].len = strlen(MROS_PACKET_FMT_XML_REQUEST) + 1;

	mros_http_post_fmt.fmt = MROS_PACKET_FMT_HTTP_POST;
	mros_http_post_fmt.len = strlen(MROS_PACKET_FMT_HTTP_POST) + 1;

	mros_http_ok_fmt.fmt = MROS_PACKET_FMT_HTTP_OK;
	mros_http_ok_fmt.len = strlen(MROS_PACKET_FMT_HTTP_OK) + 1;

	return MROS_E_OK;
}

static mRosSizeType get_arglen(mRosEncodeArgType &arg)
{
	mRosSizeType len = 0;
	for (mRosSizeType i = 0; i < arg.args; i++) {
		len += strlen(arg.argv[i]) + 1;
	}
	return len;
}

mRosReturnType mRosPacketEncoder::encode(mRosEncodeArgType &arg, mRosPacketType &packet)
{
	if (arg.type >= MROS_PACKET_DATA_NUM) {
		return MROS_E_RANGE;
	}
	return encode_table[arg.type](arg, packet);
}

static mRosReturnType encode_register_publisher(mRosEncodeArgType &arg, mRosPacketType &packet)
{
	mRosSizeType len;
	mRosSizeType off = 0;
	mRosSizeType xml_len;

	len = get_arglen(arg);
	len += mros_http_post_fmt.len;
	len += mros_xml_fmt_table[arg.type].len;

	//TODO add tcp ros header size..
	if (len > packet.total_size) {
		return MROS_E_NOMEM;
	}
	xml_len = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_XML_REGISTER,
			arg.argv[0],
			arg.argv[1],
			arg.argv[2],
			arg.argv[3],
			arg.argv[4]);

	snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_HTTP_POST MROS_PACKET_FMT_XML_REGISTER,
			xml_len,
			arg.argv[0],
			arg.argv[1],
			arg.argv[2],
			arg.argv[3],
			arg.argv[4]);

	return MROS_E_OK;
}
static mRosReturnType encode_register_subscriber(mRosEncodeArgType &arg, mRosPacketType &packet)
{
	mRosSizeType len;
	mRosSizeType off = 0;
	mRosSizeType xml_len;

	len = get_arglen(arg);
	len += mros_http_post_fmt.len;
	len += mros_xml_fmt_table[arg.type].len;

	//TODO add tcp ros header size..
	if (len > packet.total_size) {
		return MROS_E_NOMEM;
	}
	xml_len = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_XML_REGISTER,
			arg.argv[0],
			arg.argv[1],
			arg.argv[2],
			arg.argv[3],
			arg.argv[4]);

	snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_HTTP_POST MROS_PACKET_FMT_XML_REGISTER,
			xml_len,
			arg.argv[0],
			arg.argv[1],
			arg.argv[2],
			arg.argv[3],
			arg.argv[4]);

	return MROS_E_OK;
}
static mRosReturnType encode_request_topic(mRosEncodeArgType &arg, mRosPacketType &packet)
{
	mRosSizeType len;
	mRosSizeType off = 0;
	mRosSizeType xml_len;

	len = get_arglen(arg);
	len += mros_http_post_fmt.len;
	len += mros_xml_fmt_table[arg.type].len;

	//TODO add tcp ros header size..
	if (len > packet.total_size) {
		return MROS_E_NOMEM;
	}
	xml_len = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_XML_REQUEST,
			arg.argv[0],
			arg.argv[1],
			arg.argv[2],
			arg.argv[3]);

	snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_HTTP_POST MROS_PACKET_FMT_XML_REQUEST,
			xml_len,
			arg.argv[0],
			arg.argv[1],
			arg.argv[2],
			arg.argv[3]);

	return MROS_E_OK;
}
