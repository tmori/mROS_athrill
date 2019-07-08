#include "mros_topic_callback.h"

#include <string>


//TODO callback
void mros_topic_callback(mRosFuncIdType func_id, const char *data)
{
	void (*fp)(std::string *ptr);
	fp = (void (*)(std::string *))func_id;
	std::string msg((const char*)data);
	fp(&msg);
	return;
}
