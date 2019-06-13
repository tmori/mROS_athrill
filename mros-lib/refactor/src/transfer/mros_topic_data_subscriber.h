#ifndef _MROS_TOPIC_DATA_SUBSCRIBER_H_
#define _MROS_TOPIC_DATA_SUBSCRIBER_H_


#include "mros_types.h"

namespace mros {
namespace transfer {

class RosTopicDataSubscriber {
public:
	static mRosReturnType init(void);
	static void subscribe(void);
private:
	RosTopicDataSubscriber();
	~RosTopicDataSubscriber();
};

}
}

#endif /* _MROS_TOPIC_DATA_SUBSCRIBER_H_ */

