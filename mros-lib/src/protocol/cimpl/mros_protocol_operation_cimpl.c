#include "mros_protocol_operation_cimpl.h"
#include "mros_comm_tcp_client_factory_cimpl.h"
#include "mros_packet_encoder_cimpl.h"
#include "mros_packet_decoder_cimpl.h"
#include "mros_memory.h"
#include "mros_config.h"

mRosReturnType mros_protocol_topic_data_send(mRosCommTcpClientType *client, mRosMemoryManagerType *mempool, const char *data, mRosSizeType datalen)
{
	mRosReturnType ret;
	mRosSizeType res;
	mRosPacketType packet;
	mRosMemoryListEntryType *mem_entryp;
	mRosEncodeArgType arg;

	ret = mros_mem_alloc(mempool, datalen + MROS_TOPIC_RAWDATA_HEADER_SIZE, &mem_entryp);
	if (ret != MROS_E_OK) {
		return ret;
	}
	packet.total_size = mem_entryp->data.memsize;
	packet.data_size = mem_entryp->data.size;
	packet.data = mem_entryp->data.memp;


	arg.type = MROS_PACKET_DATA_TOPIC;
	arg.args_int = 1;
	arg.argi[0] = datalen;
	arg.args_char = 1;
	arg.argv[0] = data;

	ret = mros_packet_encode(&arg, &packet);
	if (ret != MROS_E_OK) {
		goto done;
	}
	ret = mros_comm_tcp_client_send_all(client, packet.data, packet.data_size, &res);

done:
	mros_mem_free(mempool, mem_entryp);
	return ret;
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
	ret = mros_packet_get_body_size(&packet, &len);
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


