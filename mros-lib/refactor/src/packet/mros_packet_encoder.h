#ifndef _MROS_PACKET_ENCODER_H_
#define _MROS_PACKET_ENCODER_H_

#include "mros_packet.h"

namespace mros {
namespace packet {

#define MROS_ENCODE_ARGS_MAX	5
typedef struct {
	mRosPacketDataType type;
	mRosSizeType	args;
	const char* 	argv[MROS_ENCODE_ARGS_MAX];
} mRosEncodeArgType;

class mRosPacketEncoder {
public:
	static mRosReturnType encode(mRosEncodeArgType &arg, mRosPacketType &packet);

private:
	mRosPacketEncoder();
	~mRosPacketEncoder();
};


}
}


#endif /* _MROS_PACKET_ENCODER_H_ */
