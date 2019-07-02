#ifndef _MROS_NODE_CIMPL_H_
#define _MROS_NODE_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_list.h"
#include "mros_config.h"

typedef enum {
	MROS_NODE_TYPE_INNER = 0,
	MROS_NODE_TYPE_OUTER,
	MROS_NODE_TYPE_NUM,
} mRosNodeEnumType;

typedef struct {
	mRosNodeIdType				node_id;
	mRosTaskIdType				task_id;
	char						node_name[MROS_NODE_NAME_MAXLEN];
	mros_uint32					namelen;
} mRosNodeEntryType;

#define MROS_TOPIC_NODE_ENTRY_INIT(entryp)	\
do {	\
	(entryp)->data.node_id = MROS_ID_NONE;	\
	(entryp)->data.namelen = 0;	\
} while (0)

typedef ListEntryType(mRosNodeListEntryType, mRosNodeEntryType) mRosNodeListEntryType;
typedef ListHeadType(mRosNodeListEntryType) mRosNodeEntryHeadType;

typedef struct {
	mRosNodeEntryHeadType	 	head;
	mRosNodeListEntryType 		*node_entries;
	mRosSizeType				max_node;
} mRosNodeManagerType;

extern mRosReturnType mros_node_init(void);
extern mRosReturnType mros_node_get_byname(const char *node_name, mRosNodeIdType *id);
extern mRosReturnType mros_node_get_bytid(mRosNodeIdType *id);
extern mRosNodeEnumType mros_node_type(mRosNodeIdType id);
extern const char* mros_node_name(mRosNodeIdType id);

extern mRosReturnType mros_node_create_inner(const char *node_name, mRosNodeIdType *id);
extern mRosReturnType mros_node_create_outer(mRosNodeIdType *id);

extern mRosReturnType mros_node_remove(mRosNodeIdType id);

/*
 * Topic Node Config APIs
 */
#define MROS_TOPIC_NODE_CONFIG_DECLARE_MANAGER(tnode_instance_name, max_node)	\
	static mRosNodeListEntryType tnode_instance_name##_array [(node_num)];	\
	static mRosNodeManagerType tnode_instance_name##_mgr;	\
	static mRosNodeConfigType  tnode_instance_name##_config = {	\
		(max_node),	\
		tnode_config_name##_array,	\
	};


#ifdef __cplusplus
}
#endif
#endif /* _MROS_NODE_CIMPL_H_ */
