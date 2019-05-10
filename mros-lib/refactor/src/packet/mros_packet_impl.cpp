#include "mros_packet.h"
#include <stdlib.h>

using namespace mros::packet;
using namespace mros::memory;

static mRosMemory *packet_memory_manager = NULL;

mRosReturnType mRosPacket::init(mRosMemory &memory_manager)
{
	if (packet_memory_manager != NULL) {
		return MROS_E_INVAL;
	}
	packet_memory_manager = &memory_manager;
	return MROS_E_OK;
}

mRosReturnType mRosPacket::get(mRosPacketType &packet, mRosSizeType size)
{
	if (packet_memory_manager == NULL) {
		return MROS_E_INVAL;
	}
	mRosReturnType ret = packet_memory_manager->memory_alloc(size, &packet.data);
	if (ret != MROS_E_OK) {
		return ret;
	}
	packet.total_size = size;
	packet.data_size = 0;
	return MROS_E_OK;
}
mRosReturnType mRosPacket::put(mRosPacketType &packet)
{
	if (packet_memory_manager == NULL) {
		return MROS_E_INVAL;
	}
	return packet_memory_manager->memory_free(*(packet.data));
}

