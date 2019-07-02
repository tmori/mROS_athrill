#include "mros_protocol_slave_cimpl.h"
#include "mros_protocol_server_proc_cimpl.h"
#include "mros_comm_tcp_client_cimpl.h"
#include "mros_comm_tcp_server_cimpl.h"
#include "mros_types.h"
#include "mros_config.h"
#include "mros_packet_encoder_cimpl.h"

typedef union {
	char buffer;
	char buffer1[MROS_PACKET_MAXSIZE_REQ_REQUEST_TOPIC];
	char buffer2[MROS_PACKET_MAXSIZE_RES_REQUEST_TOPIC];
} mRosSlavePacketBufferType;
static mRosSlavePacketBufferType mros_slave_packet_buffer;

typedef struct {
	mRosProtocolSlaveStateEnumType 		state;
	mRosEncodeArgType 					arg;
	mRosPacketType						packet;
	mRosCommTcpServerType				server_comm;
	mRosCommTcpClientType				client_comm;
} mRosProtocolSlaveType;

static mRosProtocolSlaveType mros_protocol_slave;

mRosReturnType mros_protocol_slave_init(void)
{
	mRosReturnType ret = mros_comm_tcp_server_init(&mros_protocol_slave.server_comm);
	if (ret != MROS_E_OK) {
		return ret;
	}
	(void)mros_comm_socket_set_blocking(&mros_protocol_slave.server_comm.socket, MROS_FALSE, MROS_SLAVE_TIMEOUT);

	mros_protocol_slave.packet.total_size = sizeof(mRosSlavePacketBufferType);
	mros_protocol_slave.packet.data = &mros_slave_packet_buffer.buffer;
	mros_protocol_slave.state = MROS_PROTOCOL_SLAVE_STATE_WAITING;
	ret =  mros_comm_tcp_server_bind(&mros_protocol_slave.server_comm, MROS_SLAVE_PORT_NO);
	if (ret != MROS_E_OK) {
		return ret;
	}
	ret = mros_comm_tcp_server_listen(&mros_protocol_slave.server_comm, MROS_COMM_TCP_SERVER_LISTEN_MAX_DEFAULT_VALUE);
	if (ret != MROS_E_OK) {
		return ret;
	}
	return MROS_E_OK;
}

void mros_protocol_slave_run(void)
{
	mRosReturnType ret;

	while (MROS_TRUE) {
		ret = mros_comm_tcp_server_accept(&mros_protocol_slave.server_comm, &mros_protocol_slave.client_comm);
		if (ret != MROS_E_OK) {
			continue;
		}
		ret = mros_proc_receive(&mros_protocol_slave.client_comm, &mros_protocol_slave.packet);
		if (ret != MROS_E_OK) {
			//TODO ERRLOG
			mros_comm_tcp_client_close(&mros_protocol_slave.client_comm);
			continue;
		}
		ret = mros_proc_slave(&mros_protocol_slave.client_comm, &mros_protocol_slave.packet);
		if (ret != MROS_E_OK) {
			//TODO ERRLOG
			continue;
		}
		mros_comm_tcp_client_close(&mros_protocol_slave.client_comm);
	}
	return;
}
