#include "mros_topic.h"
#include "mros_memory.h"
#include "mros_list.h"
#include <stdlib.h>
#include <string.h>

#include "mros_topic_cimpl.h"


using namespace mros::topic;

mRosReturnType mRosTopic::init(void)
{
	return mros_topic_init();
}

mRosContainerObjType mRosTopic::get_first(void)
{
	return mros_topic_get_first();
}

mRosContainerObjType mRosTopic::get_next(mRosContainerObjType obj)
{
	return mros_topic_get_next(obj);
}
const char* mRosTopic::get_topic_name(mRosTopicIdType id)
{
	return mros_topic_get_topic_name(id);
}

mRosTopicIdType mRosTopic::get_id(mRosContainerObjType obj)
{
	return mros_topic_get_id(obj);
}

mRosReturnType mRosTopic::get(const char *topic_name, mRosTopicIdType &id)
{
	return mros_topic_get(topic_name, &id);
}

mRosReturnType mRosTopic::create(const char *topic_name, mRosTopicIdType &id)
{
	return mros_topic_create(topic_name, &id);
}

mRosReturnType mRosTopic::create(const char *topic_name)
{
	mRosTopicIdType id;
	return mros_topic_create(topic_name, &id);
}

mRosReturnType mRosTopic::set_quesize(const char *topic_name, mRosSizeType size)
{
	return mros_topic_set_quesize_byname(topic_name, size);
}
mRosReturnType mRosTopic::set_quesize(mRosTopicIdType id, mRosSizeType size)
{
	return mros_topic_set_quesize_byid(id, size);
}

mRosReturnType mRosTopic::remove(const char *topic_name)
{
	return mros_topic_remove_byname(topic_name);
}
mRosReturnType mRosTopic::remove(mRosTopicIdType id)
{
	return mros_topic_remove_byid(id);
}

mRosReturnType mRosTopic::add_data(mRosTopicIdType id, mRosMemoryListEntryType &data)
{
	return mros_topic_add_data(id, &data);
}

mRosReturnType mRosTopic::get_data(mRosTopicIdType id, mRosMemoryListEntryType **data)
{
	return mros_topic_get_data(id, data);
}

mRosTopic::mRosTopic()
{
	//nothing to do
}

mRosTopic::~mRosTopic()
{
	//nothing to do
}
