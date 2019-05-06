#ifndef _MROS_PACKET_DECODER_H_
#define _MROS_PACKET_DECODER_H_

#include "mros_packet.h"
#include <string>

namespace mros {
namespace packet {

class mRosPacketDecoder {
public:
	static mRosReturnType decode_port(mros_uint32 &port, mRosPacketType &packet);
	static mRosReturnType decode_port(std::string &port, mRosPacketType &packet);
	static mRosReturnType decode_ip(std::string &ip, mRosPacketType &packet);

	static mRosReturnType decode_method(std::string &method, mRosPacketType &packet);
	static mRosReturnType decode_topic_type(std::string &topic_type, mRosPacketType &packet);
	static mRosReturnType decode_topic_name(std::string &topic_name, mRosPacketType &packet);
	static mRosReturnType decode_caller_id(std::string &caller_id, mRosPacketType &packet);
	static mRosReturnType decode_message_definition(std::string &msgdef, mRosPacketType &packet);
	static mRosReturnType decode_fptr(std::string &fptr, mRosPacketType &packet);
	static mRosReturnType decode_req_topic_name(std::string &topic_name, mRosPacketType &packet);
private:
	mRosPacketDecoder();
	~mRosPacketDecoder();
};


}
}

#endif /* _MROS_PACKET_DECODER_H_ */
