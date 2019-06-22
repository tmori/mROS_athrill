#include "mros_topic_data_subscriber_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"
#include "mros_topic_cimpl.h"
#include <stdlib.h>

static void mros_topic_subscribe(mRosTopicConnectorManagerType *mgrp, mRosContainerObjType topic_obj)
{
	mRosReturnType ret;
	mRosContainerObjType obj;
	mRosMemoryListEntryType *topic_data;
	mRosTopicIdType topic_id;

	ret = mros_topic_connector_get_topic(topic_obj, &topic_id);
	if (ret != MROS_E_OK) {
		return;
	}

	obj = mros_topic_connector_get_first(mgrp, topic_obj);
	if (obj == MROS_COBJ_NULL) {
		return;
	}
	ret = mros_topic_get_data(topic_id, &topic_data);
	if (ret != MROS_E_OK) {
		//TODO free topic_data;
		return;
	}

	while (obj != MROS_COBJ_NULL) {
		ret = mros_topic_connector_add_data(obj, topic_data);
		if (ret != MROS_E_OK) {
			//TOODO ERROR LOG
			continue;
		}
		obj = mros_topic_connector_get_next(mgrp, topic_obj, obj);
	}

	//TODO free topic_data
	return;
}

mRosReturnType mros_topic_data_subscriber_init(void)
{
	return MROS_E_OK;
}

void mros_topic_data_subscriber_run(void)
{
	mRosContainerObjType topic_obj;
	mRosTopicConnectorManagerType *mgrp;

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_SUB);
	if (mgrp == NULL) {
		return;
	}
	topic_obj = mros_topic_connector_get_topic_first(mgrp);
	while (topic_obj != MROS_COBJ_NULL) {
		mros_topic_subscribe(mgrp, topic_obj);
		topic_obj = mros_topic_connector_get_topic_next(mgrp, topic_obj);
	}
	return;
}
