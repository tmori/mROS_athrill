#ifndef _MROS_TOPIC_H_
#define _MROS_TOPIC_H_

#include "mros_types.h"

namespace mros {
namespace topic {

class RosTopic {
public:
	static mRosReturnType get(const char *topic_name, RosTopicIdType &id);
	static mRosReturnType create(const char *topic_name, RosTopicIdType &id);
	static mRosReturnType create(const char *topic_name);
	static mRosReturnType remove(const char *topic_name);
	static mRosReturnType remove(RosTopicIdType id);
	RosTopicIdType id()
	{
		return topic_id;
	}

private:
	RosTopic(const char *name);
	~RosTopic();
	RosTopicIdType		topic_id;
	const char			*topic_name;

};
}
}



#endif /* _MROS_TOPIC_H_ */
