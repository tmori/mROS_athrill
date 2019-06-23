#include "mros_topic_connector_factory_cimpl.h"
#include "mros_topic_cimpl.h"
#include <stdlib.h>
#include "mros_topic_data_subscriber_cimpl.h"

static void mros_topic_publish(mRosTopicConnectorManagerType *mgrp, mRosContainerObjType topic_obj)
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
	while (obj != MROS_COBJ_NULL) {
		topic_data = mros_topic_connector_get_data(obj);
		if (topic_data == NULL) {
			continue;
		}
		ret = mros_topic_add_data(topic_id, topic_data);
		if (ret != MROS_E_OK) {
			(void)mros_mem_free(topic_data->data.mgrp, topic_data);
			continue;
		}
		obj = mros_topic_connector_get_next(mgrp, topic_obj, obj);
	}

	return;
}

mRosReturnType mros_topic_data_publisher_init(void)
{
	return MROS_E_OK;
}

void mros_topic_data_publisher_run(void)
{
	mRosContainerObjType topic_obj;
	mRosTopicConnectorManagerType *mgrp;

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_PUB);
	if (mgrp == NULL) {
		return;
	}
	topic_obj = mros_topic_connector_get_topic_first(mgrp);
	while (topic_obj != MROS_COBJ_NULL) {

		mros_topic_publish(mgrp, topic_obj);
		topic_obj = mros_topic_connector_get_topic_next(mgrp, topic_obj);
	}
	return;
}
