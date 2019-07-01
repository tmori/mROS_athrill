#include "mros_protocol_operation_cimpl.h"
#include "mros_comm_tcp_client_factory_cimpl.h"
#include "mros_packet_encoder_cimpl.h"
#include "mros_packet_decoder_cimpl.h"
#include "mros_memory.h"
#include "mros_config.h"

mRosReturnType mros_protocol_topic_data_send(mRosCommTcpClientType *client, const char *data, mRosSizeType datalen)
{
	mRosReturnType ret;
	mRosSizeType res;
	mRosPacketType packet;

	ret = mros_comm_tcp_client_send_all(client, (const char*)&packet.data_size, sizeof(packet.data_size), &res);
	if (ret != MROS_E_OK) {
		return ret;
	}

	return mros_comm_tcp_client_send_all(client, packet.data, packet.data_size, &res);
}

mRosMemoryListEntryType* mros_protocol_topic_data_receive(mRosCommTcpClientType *client, mRosMemoryManagerType *mempool)
{
	mRosPacketType packet;
	mRosSizeType len;
	mRosSizeType res;
	mRosReturnType ret;
	mRosMemoryListEntryType *mem_entryp;
	mros_int8 rawdata[MROS_TOPIC_RAWDATA_HEADER_SIZE];

	ret = mros_comm_socket_wait_readable(&client->socket, 0);
	if (ret != MROS_E_OK) {
		return NULL;
	}
	ret = mros_comm_tcp_client_receive_all(client, rawdata, MROS_TOPIC_RAWDATA_HEADER_SIZE, &res);
	if (ret != MROS_E_OK) {
		return NULL;
	}
	packet.total_size = MROS_TOPIC_RAWDATA_HEADER_SIZE;
	packet.data_size = MROS_TOPIC_RAWDATA_HEADER_SIZE;
	packet.data = rawdata;
	ret = mros_topicpacket_get_body_size(&packet, &len);
	if (ret != MROS_E_OK) {
		return NULL;
	}

	ret = mros_mem_alloc(mempool, len, &mem_entryp);
	if (ret != MROS_E_OK) {
		return NULL;
	}
	packet.total_size = len;
	packet.data_size = len;
	packet.data = mem_entryp->data.memp;

	ret = mros_comm_tcp_client_receive_all(client, packet.data, len, &res);
	if (ret != MROS_E_OK) {
		return NULL;
	}
	return mem_entryp;
}

void mros_protocol_client_obj_free(void* reqp)
{
	mros_comm_tcp_clientc_free((mRosCommTcpClientListReqEntryType *)reqp);
	return;
}


