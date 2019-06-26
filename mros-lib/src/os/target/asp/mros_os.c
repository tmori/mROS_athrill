#include "mros_os_target.h"

mRosTaskIdType mros_get_taskid(void)
{
	mRosTaskIdType tid;
	(void)get_tid(&tid);
	return tid;
}
