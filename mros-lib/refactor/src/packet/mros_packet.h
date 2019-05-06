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
	MROS_PACKET_DATA_NUM,
} mRosPacketDataType;

typedef struct {
	mRosSizeType						total_size;
	mRosSizeType						data_size;
	memory::mRosMemoryListEntryType 	*data;
} mRosPacketType;

class mRosPacket {
public:
	static mRosReturnType get(mRosPacketType &packet, mRosSizeType size);
	static mRosReturnType put(mRosPacketType &packet);

private:
	mRosPacket() {}
	~mRosPacket() {}
};


}
}


#endif /* _MROS_PACKET_H_ */
