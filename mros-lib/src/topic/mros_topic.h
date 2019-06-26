#ifndef _MROS_TOPIC_H_
#define _MROS_TOPIC_H_

#include "mros_types.h"
#include "mros_memory.h"

namespace mros {
namespace topic {

class mRosTopic {
public:
	static mRosReturnType init(void);
	static mRosContainerObjType get_first(void);
	static mRosContainerObjType get_next(mRosContainerObjType obj);
	static mRosTopicIdType get_id(mRosContainerObjType obj);
	static const char *get_topic_name(mRosTopicIdType id);

	static mRosReturnType get(const char *topic_name, mRosTopicIdType &id);
	static mRosReturnType create(const char *topic_name, mRosTopicIdType &id);
	static mRosReturnType create(const char *topic_name);
	static mRosReturnType remove(const char *topic_name);
	static mRosReturnType remove(mRosTopicIdType id);
	static mRosReturnType set_quesize(const char *topic_name, mRosSizeType size);
	static mRosReturnType set_quesize(mRosTopicIdType id, mRosSizeType size);
	static mRosReturnType add_data(mRosTopicIdType id, mRosMemoryListEntryType &data);
	static mRosReturnType get_data(mRosTopicIdType id, mRosMemoryListEntryType **data);

private:
	mRosTopic();
	~mRosTopic();
};
}
}



#endif /* _MROS_TOPIC_H_ */
