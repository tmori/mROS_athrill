#ifndef _MROS_PACKET_H_
#define _MROS_PACKET_H_

#include "mros_types.h"
#include "mros_memory.h"

namespace mros {
namespace packet {

typedef enum {
	MROS_PACKET_DATA_REGISTER_PUBLISHER = 0,
	MROS_PACKET_DATA_REGISTER_SUBSCRIBER,
	MROS_PACKET_DATA_REQUEST_TOPIC,
	MROS_PACKET_ENCTYPE_NUM,
} mRosPacketDataType;

typedef struct {
	RosPacketIdType				packet_id;
	mRosSizeType				header_size;
	mRosSizeType				body_size;
	memory::mRosMemoryEntryType header;
	memory::mRosMemoryEntryType body;
} mRosPacketType;

class mRosPacket {
public:
	static mRosReturnType init(mRosSizeType max_packet);
	static mRosReturnType get(mRosPacketType &packet);
	static mRosReturnType put(mRosPacketType &packet);

private:
	mRosPacket();
	~mRosPacket();
};


}
}


#endif /+ _MROS_PACKET_H_ */
