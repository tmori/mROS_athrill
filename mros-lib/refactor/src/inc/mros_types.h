#ifndef _MROS_TYPES_H_
#define _MROS_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef int mros_int32;
typedef unsigned char mros_uint8;
typedef unsigned short mros_uint16;
typedef unsigned int mros_uint32;
typedef unsigned char mros_boolean;
#define MROS_FALSE		0
#define MROS_TRUE		0

#define MROS_ID_NONE	0
#define MROS_ID(index)		((index) + 1U)
#define MROS_INDEX(id)		((id) - 1U)

typedef mros_uint32 mRosNodeIdType;
typedef mros_uint32 mRosTopicIdType;
typedef mros_uint32 mRosTopicConnectorIdType;
typedef mros_uint32 mRosPacketIdType;
typedef mros_uint32 mRosIdType;
typedef mros_uint32* mRosFuncIdType;

typedef mros_uint32* mRosContainerObjType;
#define MROS_COBJ_NULL	((mRosContainerObjType)NULL)

typedef mros_uint32 mRosSizeType;

#define MROS_E_OK			0
#define MROS_E_NOENT		2
#define MROS_E_NOMEM		12
#define MROS_E_EXIST		17
#define MROS_E_INVAL		22
#define MROS_E_RANGE		34
#define MROS_E_LIMIT		111
typedef mros_int32 mRosReturnType;

/*
 * Os dependent data types
 */
typedef mros_uint32	mRosTaskIdType;
#define MROS_TASKID_NONE	0U

#ifdef __cplusplus
}
#endif

#endif /* _MROS_TYPES_H_ */
