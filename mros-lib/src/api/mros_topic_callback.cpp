#include "mros_topic_callback.h"

#include <string>


//TODO callback
void mros_topic_callback(mRosFuncIdType func_id, const char *data, int len)
{
	void (*fp)(std::string *ptr);
	fp = (void (*)(std::string *))func_id;

	std::string msg((const char*)data, len);
	fp(&msg);
	return;
}
