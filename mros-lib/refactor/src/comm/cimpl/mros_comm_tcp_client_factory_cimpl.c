#include "mros_comm_tcp_client_factory_cimpl.h"


static mRosCommTcpClientEntryHeadType mros_comm_tcp_client_factory;
static mRosCommTcpClientListEntryType mros_comm_tcp_client_entries[MROS_TOPIC_TCP_CLIENT_MAX_NUM];

mRosReturnType mros_comm_tcp_client_factory_init(void)
{

	List_Init(&mros_comm_tcp_client_factory, mRosCommTcpClientListEntryType, MROS_TOPIC_TCP_CLIENT_MAX_NUM, mros_comm_tcp_client_entries);
	return MROS_E_OK;
}

mRosCommTcpClientListEntryType *mros_comm_tcp_clientc_alloc(void)
{
	mRosCommTcpClientListEntryType *p;
	ListEntry_Alloc(&mros_comm_tcp_client_factory, mRosCommTcpClientListEntryType, &p);
	if (p == NULL) {
		return NULL;
	}
	ListEntry_AddEntry(&mros_comm_tcp_client_factory, p);
	return p;
}

void mros_comm_tcp_clientc_free(mRosCommTcpClientListEntryType *client)
{
	ListEntry_Free(&mros_comm_tcp_client_factory, client);
	return;
}
