#ifndef _MROS_TOPIC_CIMPL_H_
#define _MROS_TOPIC_CIMPL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mros_memory.h"
#include "mros_list.h"
#include "mros_config.h"

typedef struct {
	mRosTopicIdType				topic_id;
	const char					*topic_name;
	mros_uint32					namelen;

	/*
	 * トピックデータ格納用キュー
	 */
	mRosSizeType				queue_maxsize;
	mRosMemoryListHeadType 		queue_head;
} mRosTopicEntryType;

typedef ListEntryType(mRosTopicListEntryType, mRosTopicEntryType) mRosTopicListEntryType;
typedef ListHeadType(mRosTopicListEntryType) mRosTopicEntryHeadType;

#define MROS_TOPIC_ENTRY_INIT(entryp)	\
do {	\
	(entryp)->data.topic_name = NULL;	\
	(entryp)->data.namelen = 0;	\
	(entryp)->data.queue_maxsize = 1; \
} while (0)

typedef struct {
	mRosTopicEntryHeadType	 	head;
	mRosTopicListEntryType 		*topic_entries;
	mRosTopicIdType				max_topic;
} mRosTopicManagerType;

extern mRosReturnType mros_topic_init(void);
extern mRosContainerObjType mros_topic_get_first(void);
extern mRosContainerObjType mros_topic_get_next(mRosContainerObjType obj);
extern const char *mros_topic_get_topic_name(mRosTopicIdType id);
extern mRosTopicIdType mros_topic_get_id(mRosContainerObjType obj);
extern mRosReturnType mros_topic_get(const char *topic_name, mRosTopicIdType *id);
extern mRosReturnType mros_topic_create(const char *topic_name, mRosTopicIdType *id);
extern mRosReturnType mros_topic_set_quesize_byname(const char *topic_name, mRosSizeType size);
extern mRosReturnType mros_topic_set_quesize_byid(mRosTopicIdType id, mRosSizeType size);
extern mRosReturnType mros_topic_remove_byname(const char *topic_name);
extern mRosReturnType mros_topic_remove_byid(mRosTopicIdType id);
extern mRosReturnType mros_topic_add_data(mRosTopicIdType id, mRosMemoryListEntryType *data);
extern mRosReturnType mros_topic_get_data(mRosTopicIdType id, mRosMemoryListEntryType **data);

#ifdef __cplusplus
}
#endif
#endif /* _MROS_TOPIC_CIMPL_H_ */
