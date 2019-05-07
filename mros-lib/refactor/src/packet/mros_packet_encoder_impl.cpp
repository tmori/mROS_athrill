#include "mros_packet_encoder.h"
#include "mros_packet_fmt_xml.h"
#include "mros_packet_fmt_http.h"
#include "mros_packet_fmt_tcpros.h"
#include <string.h>
#include <stdio.h>

using namespace mros::packet;

static mRosReturnType encode_register_publisher(mRosEncodeArgType &arg, mRosPacketType &packet);
static mRosReturnType encode_register_subscriber(mRosEncodeArgType &arg, mRosPacketType &packet);
static mRosReturnType encode_request_topic(mRosEncodeArgType &arg, mRosPacketType &packet);
static mRosReturnType encode_tcpros_pub(mRosEncodeArgType &arg, mRosPacketType &packet);
static mRosReturnType encode_tcpros_sub(mRosEncodeArgType &arg, mRosPacketType &packet);
static mRosReturnType encode_topic(mRosEncodeArgType &arg, mRosPacketType &packet);

typedef mRosReturnType (*encode_table_type) (mRosEncodeArgType&, mRosPacketType&);

static encode_table_type encode_table[MROS_PACKET_DATA_NUM] = {
		encode_register_publisher,
		encode_register_subscriber,
		encode_request_topic,
		encode_tcpros_pub,
		encode_tcpros_sub,
		encode_topic,
};

typedef struct {
	const char* fmt;
	mros_uint32 len;
} mRosFmtType;

static mRosFmtType mros_xml_fmt_table[MROS_PACKET_DATA_NUM];
static mRosFmtType mros_http_post_fmt;
static mRosFmtType mros_http_ok_fmt;
static mRosFmtType mros_tcpros_pub_fmt;
static mRosFmtType mros_tcpros_sub_fmt;

static void add_len(unsigned char *buf, mros_uint32 len)
{
	//TODO shift?
    buf[0] = len - 0;
    buf[1] = (len/256) - 0;
    buf[2] = (len/65536) - 0;
    buf[3] = (len/16777216) - 0;
}


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

	mros_tcpros_pub_fmt.fmt = MROS_PACKET_FMT_TCPROS_PUB;
	mros_tcpros_pub_fmt.len = strlen(MROS_PACKET_FMT_TCPROS_PUB) + 1;

	mros_tcpros_sub_fmt.fmt = MROS_PACKET_FMT_TCPROS_SUB;
	mros_tcpros_sub_fmt.len = strlen(MROS_PACKET_FMT_TCPROS_SUB) + 1;

	return MROS_E_OK;
}

static mRosSizeType get_arglen(mRosEncodeArgType &arg)
{
	mRosSizeType len = 0;
	for (mRosSizeType i = 0; i < arg.args_char; i++) {
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

	packet.data_size = snprintf(&packet.data->data.memp[off], packet.total_size,
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

	packet.data_size = snprintf(&packet.data->data.memp[off], packet.total_size,
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

	if (len > packet.total_size) {
		return MROS_E_NOMEM;
	}
	xml_len = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_XML_REQUEST,
			arg.argv[0],
			arg.argv[1],
			arg.argv[2],
			arg.argv[3]);

	packet.data_size = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_HTTP_POST MROS_PACKET_FMT_XML_REQUEST,
			xml_len,
			arg.argv[0],
			arg.argv[1],
			arg.argv[2],
			arg.argv[3]);

	return MROS_E_OK;
}
static mRosReturnType encode_tcpros_pub(mRosEncodeArgType &arg, mRosPacketType &packet)
{
	mRosSizeType len;
	mRosSizeType off = 0;
	mRosSizeType len_callerid;
	mRosSizeType len_topic;
	mRosSizeType len_type;
	mRosSizeType len_md5sum;

	len = get_arglen(arg);
	len += mros_tcpros_pub_fmt.len;

	if (len > packet.total_size) {
		return MROS_E_NOMEM;
	}

	len_callerid = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_TCPROS_CALLER_ID, arg.argv[0]);

	len_topic = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_TCPROS_TOPIC, arg.argv[1]);

	len_type = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_TCPROS_TYPE, arg.argv[2]);

	len_md5sum = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_TCPROS_MD5SUM, arg.argv[3]);

	packet.data_size = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_TCPROS_PUB,
			arg.argv[0],
			arg.argv[1],
			arg.argv[2],
			arg.argv[3]);

	off = 0;
	add_len((unsigned char*)&packet.data->data.memp[off], packet.data_size);

	off += 4U;
	add_len((unsigned char*)&packet.data->data.memp[off], len_callerid);

	off += (4U + len_callerid);
	add_len((unsigned char*)&packet.data->data.memp[off], len_topic);

	off += (4U + len_topic);
	add_len((unsigned char*)&packet.data->data.memp[off], len_type);

	off += (4U + len_type);
	add_len((unsigned char*)&packet.data->data.memp[off], len_md5sum);

	return MROS_E_OK;
}
static mRosReturnType encode_tcpros_sub(mRosEncodeArgType &arg, mRosPacketType &packet)
{
	mRosSizeType len;
	mRosSizeType off = 0;
	mRosSizeType len_callerid;
	mRosSizeType len_tcpnodelay;
	mRosSizeType len_topic;
	mRosSizeType len_type;
	mRosSizeType len_md5sum;

	len = get_arglen(arg);
	len += mros_tcpros_pub_fmt.len;

	if (len > packet.total_size) {
		return MROS_E_NOMEM;
	}

	len_callerid = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_TCPROS_CALLER_ID, arg.argv[0]);

	len_tcpnodelay = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_TCPROS_TCPNODELAY, "1");

	len_topic = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_TCPROS_TOPIC, arg.argv[1]);

	len_type = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_TCPROS_TYPE, arg.argv[2]);

	len_md5sum = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_TCPROS_MD5SUM, arg.argv[3]);

	packet.data_size = snprintf(&packet.data->data.memp[off], packet.total_size,
			MROS_PACKET_FMT_TCPROS_SUB,
			arg.argv[0],
			arg.argv[1],
			arg.argv[2],
			arg.argv[3]);

	off = 0;
	add_len((unsigned char*)&packet.data->data.memp[off], packet.data_size);

	off += 4U;
	add_len((unsigned char*)&packet.data->data.memp[off], len_callerid);

	off += (4U + len_callerid);
	add_len((unsigned char*)&packet.data->data.memp[off], len_tcpnodelay);

	off += (4U + len_tcpnodelay);
	add_len((unsigned char*)&packet.data->data.memp[off], len_topic);

	off += (4U + len_topic);
	add_len((unsigned char*)&packet.data->data.memp[off], len_type);

	off += (4U + len_type);
	add_len((unsigned char*)&packet.data->data.memp[off], len_md5sum);

	return MROS_E_OK;
}

static mRosReturnType encode_topic(mRosEncodeArgType &arg, mRosPacketType &packet)
{
	//TODO
	mRosSizeType len = arg.argi[0] + 8U;//TODO INDIGO
	if (len <= packet.total_size) {
		return MROS_E_NOMEM;
	}

	memcpy(&packet.data->data.memp[8], &arg.argv[0], arg.argi[0]);

    add_len((unsigned char*)&packet.data->data.memp[0], arg.argi[0] + 4);
    add_len((unsigned char*)&packet.data->data.memp[4], arg.argi[0]);

	return MROS_E_OK;
}

