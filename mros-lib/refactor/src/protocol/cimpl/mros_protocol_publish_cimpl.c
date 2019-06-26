#include "mros_protocol_publish_cimpl.h"
#include "mros_protocol_server_proc_cimpl.h"
#include "mros_comm_tcp_client_cimpl.h"
#include "mros_comm_tcp_server_cimpl.h"
#include "mros_types.h"
#include "mros_config.h"

typedef union {
	char buffer;
	char buffer1[MROS_PACKET_MAXSIZE_REQ_TCPROS];
	char buffer1[MROS_PACKET_MAXSIZE_RES_TCPROS];
} mRosPublishPacketBufferType;
static mRosPublishPacketBufferType mros_publish_packet_buffer;

typedef struct {
	mRosProtocolPublishStateEnumType 	state;
	mRosEncodeArgType 					arg;
	mRosPacketType						packet;
	mRosCommTcpServerType				server_comm;
	mRosCommTcpClientType				client_comm;
} mRosProtocolPublishType;

static mRosProtocolPublishType mros_protocol_publish;

mRosReturnType mros_protocol_publish_init(void)
{
	mRosReturnType ret = mros_comm_tcp_server_init(&mros_protocol_publish.server_comm);
	if (ret != MROS_E_OK) {
		return ret;
	}
	mros_protocol_publish.packet.total_size = sizeof(mRosPublishPacketBufferType);
	mros_protocol_publish.packet.data = &mros_publish_packet_buffer.buffer;
	mros_protocol_publish.state = MROS_PROTOCOL_PUBLISH_STATE_WAITING;
	ret =  mros_comm_tcp_server_bind(&mros_protocol_publish.server_comm, MROS_PUBLISHER_PORT_NO);
	if (ret != MROS_E_OK) {
		return ret;
	}
	ret = mros_comm_tcp_server_listen(&mros_protocol_publish.server_comm, MROS_COMM_TCP_SERVER_LISTEN_MAX_DEFAULT_VALUE);
	if (ret != MROS_E_OK) {
		return ret;
	}
	return MROS_E_OK;
}

void mros_protocol_publish_run(void)
{
	mRosReturnType ret;

	while (MROS_TRUE) {
		ret = mros_comm_tcp_server_accept(&mros_protocol_publish.server_comm, &mros_protocol_publish.client_comm);
		if (ret != MROS_E_OK) {
			continue;
		}
		ret = mros_proc_tcpros_receive(&mros_protocol_publish.client_comm, &mros_protocol_publish.packet);
		if (ret != MROS_E_OK) {
			//TODO ERRLOG
			mros_comm_tcp_client_close(&mros_protocol_publish.client_comm);
			continue;
		}
		ret = mros_proc_pub(&mros_protocol_publish.client_comm, &mros_protocol_publish.packet);
		if (ret != MROS_E_OK) {
			//TODO ERRLOG
			mros_comm_tcp_client_close(&mros_protocol_publish.client_comm);
			continue;
		}
	}
	return;
}
