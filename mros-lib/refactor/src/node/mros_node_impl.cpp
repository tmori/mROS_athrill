#include "mros_node.h"
#include "mros_memory.h"
#include <stdlib.h>
#include <string.h>
#include "test_serial.h"

using namespace mros::node;
using namespace mros::memory;

typedef struct {
	RosNodeIdType				node_id;
	const char					*node_name;
	mros_uint32					namelen;
} RosNodeEntryType;

typedef ListEntryType(RosNodeListEntryType, RosNodeEntryType) RosNodeListEntryType;
typedef ListHeadType(RosNodeListEntryType) RosNodeEntryHeadType;


#define ROS_NODE_ENTRY_INIT(entryp)	\
do {	\
	(entryp)->data.node_id = MROS_ID_NONE;	\
	(entryp)->data.node_name = NULL;	\
	(entryp)->data.namelen = 0;	\
} while (0)


typedef struct {
	RosNodeEntryHeadType	 	head;
	RosNodeListEntryType 		*node_entries;
	RosNodeIdType				max_node;
} RosNodeManagerType;

#define NODE_ID(index)		((index) + 1U)
#define NODE_INDEX(id)		((id) - 1U)


static RosNodeManagerType node_manager[ROS_NODE_TYPE_NUM];
#define NODE_OBJ(type, id)		node_manager[(type)].node_entries[NODE_INDEX((id))]
#define NODE_TYPE(id)	( (id <= node_manager[ROS_NODE_TYPE_INNER].max_node) ? ROS_NODE_TYPE_INNER : ROS_NODE_TYPE_OUTER )

static mRosReturnType init_node_manager(RosNodeType type, mRosSizeType max_node)
{
	node_manager[type].node_entries = (RosNodeListEntryType *)malloc(max_node * sizeof(RosNodeListEntryType));
	//TODO ASSERT
	for (mros_uint32 i = 0; i < max_node; i++) {
		RosNodeListEntryType *entry = &(node_manager[type].node_entries[i]);
		ROS_NODE_ENTRY_INIT(entry);
		entry->data.node_id = NODE_ID(i) + (((RosNodeIdType)type) * max_node);
	}
	List_Init(&node_manager[type].head, RosNodeListEntryType, max_node, node_manager[type].node_entries);
	node_manager[type].max_node = max_node;

	return MROS_E_OK;
}
static mRosReturnType get_node(const char *node_name, mros_uint32 len, RosNodeType type, RosNodeIdType &id)
{
	RosNodeListEntryType *p;
	id = MROS_ID_NONE;
	ListEntry_Foreach(&node_manager[type].head, p) {
		if (len != p->data.namelen) {
			continue;
		}
		if (!strcmp(p->data.node_name, node_name)) {
			id = p->data.node_id;
			break;
		}
	}
	if (id == MROS_ID_NONE) {
		return MROS_E_NOENT;
	}
	return MROS_E_OK;
}

mRosReturnType RosNode::init(mRosSizeType max_node)
{
	mRosReturnType ret = init_node_manager(ROS_NODE_TYPE_INNER, max_node);
	if (ret != MROS_E_OK) {
		return ret;
	}
	ret = init_node_manager(ROS_NODE_TYPE_OUTER, max_node);
	return ret;
}
mRosReturnType RosNode::get(const char *node_name, RosNodeIdType &id)
{
	mros_uint32 len = strlen(node_name);

	mRosReturnType ret = get_node(node_name, len, ROS_NODE_TYPE_INNER, id);
	if (ret != MROS_E_OK) {
		ret = get_node(node_name, len, ROS_NODE_TYPE_OUTER, id);
	}

	return ret;
}

mRosReturnType RosNode::create(const char *node_name, RosNodeType type, RosNodeIdType &id)
{
	RosNodeListEntryType *p;

	if (type >= ROS_NODE_TYPE_NUM) {
		return MROS_E_RANGE;
	}
	mRosReturnType ret = RosNode::get(node_name, id);
	if (ret == MROS_E_OK) {
		return MROS_E_EXIST;
	}
	mros_uint32 len = strlen(node_name);

	ListEntry_Alloc(&node_manager[type].head, RosNodeListEntryType, &p);
	if (p == NULL) {
		return MROS_E_NOMEM;
	}
	id = p->data.node_id;
	p->data.namelen = len;
	p->data.node_name = node_name;
	ListEntry_AddEntry(&node_manager[type].head, p);
	return MROS_E_OK;
}

mRosReturnType RosNode::create(const char *node_name, RosNodeType type)
{
	RosTopicIdType id;
	return RosNode::create(node_name, type, id);
}

mRosReturnType RosNode::remove(const char *node_name)
{
	RosTopicIdType id;

	mRosReturnType ret = RosNode::get(node_name, id);
	if (ret != MROS_E_OK) {
		return ret;
	}
	RosNodeType type = NODE_TYPE(id);

	ListEntry_Free(&node_manager[type].head, &NODE_OBJ(type, id));
	return MROS_E_OK;
}
mRosReturnType RosNode::remove(RosNodeIdType id)
{
	RosNodeType type = NODE_TYPE(id);
	if (id > node_manager[type].max_node) {
		return MROS_E_RANGE;
	}

	ListEntry_Free(&node_manager[type].head, &NODE_OBJ(type, id));
	return MROS_E_OK;
}

mRosReturnType send(RosNodeIdType id, char *data, mRosSizeType datalen, mRosSizeType &rlen)
{
	RosNodeType type = NODE_TYPE(id);
	if (id > node_manager[type].max_node) {
		return MROS_E_RANGE;
	}
	//TODO
	return MROS_E_OK;
}


RosNode::RosNode()
{

}

RosNode::~RosNode()
{

}
