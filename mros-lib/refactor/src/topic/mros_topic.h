#ifndef _MROS_TOPIC_H_
#define _MROS_TOPIC_H_

#include "mros_types.h"
#include "mros_memory.h"
#include "primitive_container.h"

namespace mros {
namespace topic {

class RosTopic {
public:
	static mRosReturnType init(mRosSizeType max_topic);

	static mRosReturnType get_topics(PrimitiveContainer<mRosTopicIdType> &container);
	static mRosReturnType rel_topics(PrimitiveContainer<mRosTopicIdType> &container);


	static mRosReturnType get(const char *topic_name, mRosTopicIdType &id);
	static mRosReturnType create(const char *topic_name, mRosTopicIdType &id);
	static mRosReturnType create(const char *topic_name);
	static mRosReturnType remove(const char *topic_name);
	static mRosReturnType remove(mRosTopicIdType id);
	static mRosReturnType set_quesize(const char *topic_name, mRosSizeType size);
	static mRosReturnType set_quesize(mRosTopicIdType id, mRosSizeType size);
	static mRosReturnType add_data(mRosTopicIdType id, memory::mRosMemoryListEntryType &data);
	static mRosReturnType get_data(mRosTopicIdType id, memory::mRosMemoryListEntryType **data);

private:
	RosTopic();
	~RosTopic();
};
}
}



#endif /* _MROS_TOPIC_H_ */
