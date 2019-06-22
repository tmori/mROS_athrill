#include "mros_topic.h"
#include "mros_config.h"
#include "mros_topic_connector_cimpl.h"
#include <stdio.h>

using namespace mros::topic;

MROS_TOPIC_CONNECTOR_CONFIG_DECLARE_MANAGER(conn_mgr, 10);

int main(int argc, const char* argv[])
{
	mRosReturnType ret;
	mRosTopicIdType id;

	ret = mRosTopic::init();
	printf("ret=%d\n", ret);

	ret = mRosTopic::create("topic_name_test1", id);
	printf("ret=%d\n", ret);

	ret = mRosTopic::create("topic_name_test2", id);
	printf("ret=%d\n", ret);

	ret = mRosTopic::create("topic_name_test3", id);
	printf("ret=%d\n", ret);


	mRosContainerObjType obj = mRosTopic::get_first();
	while (obj != MROS_COBJ_NULL) {
		id = mRosTopic::get_id(obj);
		printf("topic_name=%s\n", mRosTopic::get_topic_name(id));
		obj = mRosTopic::get_next(obj);
	}

	ret = mros_topic_connector_init(&conn_mgr_config, &conn_mgr);
	printf("ret=%d\n", ret);

	return 0;
}
