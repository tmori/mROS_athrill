#include "mros_topic_data_subscriber_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_array_container.h"
#include "mros_usr_config.h"

static void mros_topic_subscribe(mRosTopicConnectorManagerType *mgrp, mRosNodeEnumType type, mRosContainerObjType topic_obj, mRosMemoryListEntryType *topic_data)
{
	mRosReturnType ret;
	mRosContainerObjType obj;

	obj = mros_topic_connector_get_first(mgrp, type, topic_obj);
	if (obj == MROS_COBJ_NULL) {
		return;
	}

	while (obj != MROS_COBJ_NULL) {
		ret = mros_topic_connector_send_data(obj, topic_data->data.memp, topic_data->data.size);
		if (ret != MROS_E_OK) {
			ROS_ERROR("%s %s() %u ret=%d", __FILE__, __FUNCTION__, __LINE__, ret);
		}
		obj = mros_topic_connector_get_next(mgrp, topic_obj, obj);
	}

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
	mRosMemoryListEntryType *topic_data;
	mRosTopicIdType topic_id;
	mRosReturnType ret;

	mgrp = mros_topic_connector_factory_get(MROS_TOPIC_CONNECTOR_SUB);
	if (mgrp == MROS_NULL) {
		return;
	}

	topic_obj = mros_topic_connector_get_topic_first(mgrp);
	while (topic_obj != MROS_COBJ_NULL) {
		ret = mros_topic_connector_get_topic(topic_obj, &topic_id);
		if (ret != MROS_E_OK) {
			continue;
		}
		ret = mros_topic_get_data(topic_id, &topic_data);
		if (ret == MROS_E_OK) {
			mros_topic_subscribe(mgrp, MROS_NODE_TYPE_INNER, topic_obj, topic_data);
			mros_topic_subscribe(mgrp, MROS_NODE_TYPE_OUTER, topic_obj, topic_data);
			(void)mros_mem_free(topic_data->data.mgrp, topic_data);
		}
		topic_obj = mros_topic_connector_get_topic_next(mgrp, topic_obj);
	}
	return;
}
