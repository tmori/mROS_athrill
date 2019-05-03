#ifndef _MROS_TOPIC_DATA_PUBLISHER_H_
#define _MROS_TOPIC_DATA_PUBLISHER_H_


#include "mros_types.h"

namespace mros {
namespace transfer {

class RosTopicDataPublisher {
public:
	static void publish(void);
private:
	RosTopicDataPublisher();
};

}
}

#endif _MROS_TOPIC_DATA_PUBLISHER_H_

