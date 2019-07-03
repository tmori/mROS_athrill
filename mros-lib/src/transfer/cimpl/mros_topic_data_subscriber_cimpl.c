#include "mros_topic_data_subscriber_cimpl.h"
#include "mros_topic_connector_factory_cimpl.h"
#include "mros_topic_cimpl.h"
#include "mros_array_container.h"
#include "mros_config.h"
#include <stdlib.h>

MROS_ARRAY_CONTAINER_CONFIG_DECLARE_MANAGER(mros_topic_sub_mgr, MROS_TOPIC_MAX_NUM);

static void mros_topic_subscribe(mRosTopicConnectorManagerType *mgrp, mRosNodeEnumType type, mRosContainerObjType topic_obj)
{
	mRosReturnType ret;
	mRosContainerObjType obj;
	mRosMemoryListEntryType *topic_data;
	mRosTopicIdType topic_id;

	ret = mros_topic_connector_get_topic(topic_obj, &topic_id);
	if (ret != MROS_E_OK) {
		return;
	}

	obj = mros_topic_connector_get_first(mgrp, type, topic_obj);
	if (obj == MROS_COBJ_NULL) {
		return;
	}
	ret = mros_topic_get_data(topic_id, &topic_data);
	if (ret != MROS_E_OK) {
		(void)mros_mem_free(topic_data->data.mgrp, topic_data);
		return;
	}

	while (obj != MROS_COBJ_NULL) {
		ret = mros_topic_connector_send_data(obj, topic_data->data.memp, topic_data->data.size);
		if (ret != MROS_E_OK) {
			//TOODO ERROR LOG
		}
		obj = mros_topic_connector_get_next(mgrp, topic_obj, obj);
	}

	(void)mros_mem_free(topic_data->data.mgrp, topic_data);
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
	mros_topic_sub_mgr.count = 0;

	/**************************
	 * INNER NODE
	 **************************/
	topic_obj = mros_topic_connector_get_topic_first(mgrp);
	while (topic_obj != MROS_COBJ_NULL) {
		mros_array_container_add(&mros_topic_sub_mgr, topic_obj);

		mros_topic_subscribe(mgrp, MROS_NODE_TYPE_INNER, topic_obj);
		topic_obj = mros_topic_connector_get_topic_next(mgrp, topic_obj);
	}

	/**************************
	 * OUTER NODE
	 **************************/
	mros_uint32 i;
	for (i = 0; i < mros_topic_sub_mgr.count; i++) {
		mros_topic_subscribe(mgrp, MROS_NODE_TYPE_OUTER, mros_topic_sub_mgr.array[i]);
	}
	return;
}
