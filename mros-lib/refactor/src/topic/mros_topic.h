#ifndef _MROS_TOPIC_H_
#define _MROS_TOPIC_H_

#include "mros_types.h"
#include "mros_memory.h"

namespace mros {
namespace topic {

class RosTopic {
public:
	static mRosReturnType init(mRosSizeType max_topic);
	static mRosReturnType get(const char *topic_name, RosTopicIdType &id);
	static mRosReturnType create(const char *topic_name, RosTopicIdType &id);
	static mRosReturnType create(const char *topic_name);
	static mRosReturnType remove(const char *topic_name);
	static mRosReturnType remove(RosTopicIdType id);
	static mRosReturnType set_quesize(const char *topic_name, mRosSizeType size);
	static mRosReturnType set_quesize(RosTopicIdType id, mRosSizeType size);
	static mRosReturnType add_data(RosTopicIdType id, memory::mRosMemoryListEntryType &data);
	static mRosReturnType get_data(RosTopicIdType id, memory::mRosMemoryListEntryType **data);

private:
	RosTopic();
	~RosTopic();
};
}
}



#endif /* _MROS_TOPIC_H_ */