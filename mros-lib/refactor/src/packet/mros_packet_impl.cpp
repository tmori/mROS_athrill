#include "mros_packet.h"
#include <stdlib.h>

using namespace mros::packet;
using namespace mros::memory;

mRosReturnType mRosPacket::get(mRosPacketType &packet, mRosSizeType size)
{
	mRosReturnType ret = mRosMemory::memory_alloc(size, &packet.data);
	if (ret != MROS_E_OK) {
		return ret;
	}
	packet.total_size = size;
	packet.data_size = 0;
	return MROS_E_OK;
}
mRosReturnType mRosPacket::put(mRosPacketType &packet)
{
	return mRosMemory::memory_free(*(packet.data));
}

