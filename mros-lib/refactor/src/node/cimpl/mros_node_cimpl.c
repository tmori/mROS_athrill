#include "mros_node_cimpl.h"
#include "mros_os.h"
#include "mros_config.h"
#include <string.h>
#include <stdlib.h>

static mRosNodeManagerType node_manager[ROS_NODE_TYPE_NUM];
#define NODE_OBJ(type, id)		node_manager[(type)].node_entries[MROS_INDEX((id))]
#define NODE_TYPE(id)	( (id <= node_manager[ROS_NODE_TYPE_INNER].max_node) ? ROS_NODE_TYPE_INNER : ROS_NODE_TYPE_OUTER )

static mRosNodeListEntryType node_entries[ROS_NODE_TYPE_NUM][MROS_NODE_MAX_NUM];

#define NODE_MAX_ID(type)	( \
	(type == ROS_NODE_TYPE_INNER) ? \
			node_manager[ROS_NODE_TYPE_INNER].max_node :  \
			(node_manager[ROS_NODE_TYPE_INNER].max_node + node_manager[ROS_NODE_TYPE_OUTER].max_node) \
	)

mRosReturnType mros_node_init(void)
{
	for (mros_uint32 i = 0; i < ROS_NODE_TYPE_NUM; i++) {
		node_manager[i].node_entries = node_entries[i];
		for (mros_uint32 j = 0; j < MROS_NODE_MAX_NUM; j++) {
			mRosNodeListEntryType *entry = &(node_manager[i].node_entries[j]);
			MROS_TOPIC_NODE_ENTRY_INIT(entry);
			entry->data.node_id = MROS_ID(i) + (((mRosNodeIdType)i) * MROS_NODE_MAX_NUM);
		}
		List_Init(&node_manager[i].head, mRosNodeListEntryType, MROS_NODE_MAX_NUM, node_manager[i].node_entries);
		node_manager[i].max_node = MROS_NODE_MAX_NUM;
	}
	return MROS_E_OK;
}

static mRosReturnType mros_node_get_node(const char *node_name, mros_uint32 len, mRosNodeEnumType type, mRosNodeIdType *id)
{
	mRosNodeListEntryType *p;
	*id = MROS_ID_NONE;
	ListEntry_Foreach(&node_manager[type].head, p) {
		if (len != p->data.namelen) {
			continue;
		}
		if (!strcmp(p->data.node_name, node_name)) {
			*id = p->data.node_id;
			break;
		}
	}
	if (*id == MROS_ID_NONE) {
		return MROS_E_NOENT;
	}
	return MROS_E_OK;
}

mRosReturnType mros_node_get_byname(const char *node_name, mRosNodeIdType *id)
{
	mros_uint32 len = strlen(node_name);

	mRosReturnType ret = mros_node_get_node(node_name, len, ROS_NODE_TYPE_INNER, id);
	if (ret != MROS_E_OK) {
		ret = mros_node_get_node(node_name, len, ROS_NODE_TYPE_OUTER, id);
	}

	return ret;
}

mRosReturnType mros_node_get_bytid(mRosNodeIdType *id)
{
	mRosTaskIdType task_id;
	task_id = mros_get_taskid();
	mRosNodeListEntryType *p;

	*id = MROS_ID_NONE;
	ListEntry_Foreach(&node_manager[ROS_NODE_TYPE_INNER].head, p) {
		if (task_id == p->data.node_id) {
			*id = p->data.node_id;
			break;
		}
	}
	if (*id == MROS_ID_NONE) {
		return MROS_E_NOENT;
	}
	return MROS_E_OK;
}

mRosNodeEnumType mros_node_type(mRosNodeIdType id)
{
	mRosNodeEnumType type = NODE_TYPE(id);
	if (id > NODE_MAX_ID(type)) {
		return ROS_NODE_TYPE_NUM;
	}
	return type;
}

static mRosReturnType mros_node_create(const char *node_name, mRosTaskIdType task_id, mRosNodeEnumType type, mRosNodeIdType *id)
{
	mRosNodeListEntryType *p;
	mros_uint32 len = 0;
	mRosReturnType ret;

	if (type >= ROS_NODE_TYPE_NUM) {
		return MROS_E_RANGE;
	}

	if (node_name != NULL) {
		ret = mros_node_get_byname(node_name, id);
		if (ret == MROS_E_OK) {
			return MROS_E_EXIST;
		}
		len = strlen(node_name);
	}
	else {
		/* outer node */
	}

	ListEntry_Alloc(&node_manager[type].head, mRosNodeListEntryType, &p);
	if (p == NULL) {
		return MROS_E_NOMEM;
	}
	*id = p->data.node_id;
	p->data.namelen = len;
	p->data.node_name = node_name;
	ListEntry_AddEntry(&node_manager[type].head, p);
	return MROS_E_OK;
}

mRosReturnType mros_node_create_inner(const char *node_name, mRosNodeIdType *id)
{
	mRosTaskIdType task_id;
	task_id = mros_get_taskid();
	return mros_node_create(node_name, task_id, ROS_NODE_TYPE_INNER, id);
}

mRosReturnType mros_node_create_outer(mRosNodeIdType *id)
{
	return mros_node_create(NULL, MROS_TASKID_NONE, ROS_NODE_TYPE_OUTER, id);
}

mRosReturnType mros_node_remove(mRosNodeIdType id)
{
	mRosNodeEnumType type = NODE_TYPE(id);
	if (id > NODE_MAX_ID(type)) {
		return MROS_E_RANGE;
	}

	ListEntry_Free(&node_manager[type].head, &NODE_OBJ(type, id));
	return MROS_E_OK;
}
