#ifndef _MROS_TYPES_H_
#define _MROS_TYPES_H_

typedef int mros_int32;
typedef unsigned int mros_uint32;

#define MROS_ID_NONE	0
typedef mros_uint32 RosNodeIdType;
typedef mros_uint32 RosTopicIdType;
typedef mros_uint32 RosTopicConnectorIdType;
typedef mros_uint32 RosFuncIdType;
typedef mros_uint32 mRosIdType;

typedef mros_uint32 mRosSizeType;

#define MROS_E_OK			0
#define MROS_E_NOENT		2
#define MROS_E_NOMEM		12
#define MROS_E_EXIST		17
typedef mros_int32 mRosReturnType;

#endif /* _MROS_TYPES_H_ */
