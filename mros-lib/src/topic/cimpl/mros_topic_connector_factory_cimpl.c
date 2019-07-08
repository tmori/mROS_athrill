#include "mros_topic_connector_factory_cimpl.h"
#include "mros_sys_config.h"

static mros_boolean mros_topic_connector_is_inialized[MROS_TOPIC_CONNECTOR_NUM] = {
	MROS_FALSE,
	MROS_FALSE,
};

MROS_TOPIC_CONNECTOR_CONFIG_DECLARE_MANAGER(pub_connector_mgr, (MROS_PUB_TOPIC_CONNECTOR_MAX_NUM) );
MROS_TOPIC_CONNECTOR_CONFIG_DECLARE_MANAGER(sub_connector_mgr, (MROS_SUB_TOPIC_CONNECTOR_MAX_NUM) );

mRosTopicConnectorManagerType *mros_topic_connector_factory_create(mRosTopicConnectorEnumType type)
{
	mRosTopicConnectorManagerType *mgrp = MROS_NULL;
	mRosTopicConnectorConfigType *cfgp = MROS_NULL;
	mRosReturnType ret;

	switch (type) {
	case MROS_TOPIC_CONNECTOR_PUB:
		mgrp = &pub_connector_mgr;
		cfgp = &pub_connector_mgr_config;
		break;
	case MROS_TOPIC_CONNECTOR_SUB:
		mgrp = &sub_connector_mgr;
		cfgp = &sub_connector_mgr_config;
		break;
	default:
		break;
	}
	if (mgrp == MROS_NULL) {
		return MROS_NULL;
	}
	if (mros_topic_connector_is_inialized[type] == MROS_TRUE) {
		return mgrp;
	}
	ret = mros_topic_connector_init(cfgp, mgrp);
	if (ret != MROS_E_OK) {
		return MROS_NULL;
	}
	mros_topic_connector_is_inialized[type] = MROS_TRUE;
	return mgrp;
}

mRosTopicConnectorManagerType *mros_topic_connector_factory_get(mRosTopicConnectorEnumType type)
{
	mRosTopicConnectorManagerType *mgrp = MROS_NULL;

	switch (type) {
	case MROS_TOPIC_CONNECTOR_PUB:
		mgrp = &pub_connector_mgr;
		break;
	case MROS_TOPIC_CONNECTOR_SUB:
		mgrp = &sub_connector_mgr;
		break;
	default:
		break;
	}
	if (mgrp == MROS_NULL) {
		return MROS_NULL;
	}
	if (mros_topic_connector_is_inialized[type] == MROS_FALSE) {
		return MROS_NULL;
	}
	return mgrp;
}
