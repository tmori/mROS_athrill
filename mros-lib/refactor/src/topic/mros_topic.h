#ifndef _MROS_TOPIC_H_
#define _MROS_TOPIC_H_

#include "mros_types.h"

namespace mros {
namespace topic {

class RosTopic {
public:
	RosTopic(const char *name);
	RosTopicIdType id()
	{
		return topic_id;
	}
	~RosTopic();

private:
	RosTopicIdType		topic_id;
	const char			*topic_name;

};
}
}



#endif /* _MROS_TOPIC_H_ */
