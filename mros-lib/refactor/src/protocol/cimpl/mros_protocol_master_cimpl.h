#ifndef _MROS_PROTOCOL_MASTER_CIMPL_H_
#define _MROS_PROTOCOL_MASTER_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_types.h"

typedef enum {
	MROS_PROTOCOL_MASTER_STATE_WAITING = 0,
	MROS_PROTOCOL_MASTER_STATE_REGISTER_PUBLISHER,
	MROS_PROTOCOL_MASTER_STATE_REGISTER_SUBSCRIBER,
	MROS_PROTOCOL_MASTER_STATE_REQUESTING_TOPIC,
} mRosProtocolMasterStateType;

/*
 * ・ノードID(caller_id)
 * ・トピック名(topic)
 * ・トピック・データ型(topic_type)
 * ・自マシンのIP，ポート(1141)(caller_api)
 */
typedef struct {
	mRosContainerObjType connector_obj;
} mRosProtocolMasterRequestType;

extern mRosReturnType mros_protocol_master_init(void);
extern mRosReturnType mros_protocol_master_register_publisher(mRosProtocolMasterRequestType *pub_req);
extern mRosReturnType mros_protocol_master_register_subscriber(mRosProtocolMasterRequestType *sub_req);


#ifdef __cplusplus
}
#endif
#endif /* _MROS_PROTOCOL_MASTER_CIMPL_H_ */
