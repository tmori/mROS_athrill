#include "mros_memory.h"
#include <stdlib.h>


#define MEMORY_ID(index)		((index) + 1U)
#define MEMORY_INDEX(id)		((id) - 1U)

#define MEMORY_OBJ(mid, id)		memory_manager[(mid)].memory_entries[MEMORY_INDEX((id))]

mRosReturnType mros_mem_init(mRosSizeType config_num, mRosMemoryConfigType **config, mRosMemoryManagerType *mgrp)
{
	mgrp->mgr_num = config_num;
	for (mros_uint32 i = 0; i < config_num; i++) {
		mgrp->mgr_array[i].max_memory_num = config[i]->max_memory_num;
		mgrp->mgr_array[i].memsize = config[i]->memsize;

		mgrp->mgr_array[i].memory_entries = config[i]->memory_entries;
		mgrp->mgr_array[i].memory = config[i]->memory;

		for (mros_uint32 j = 0; j < mgrp->mgr_array[i].max_memory_num; j++) {
			mRosMemoryListEntryType *entry = &(mgrp->mgr_array[i].memory_entries[j]);
			entry->data.header_id = (mRosMemorySizeIdType)i;
			entry->data.memory_id = MEMORY_ID(j);
			entry->data.memsize = mgrp->mgr_array[i].memsize;
			entry->data.size = 0;
			entry->data.memp = &(mgrp->mgr_array[i].memory[(mgrp->mgr_array[i].memsize * j)]);
		}
		List_Init(&mgrp->mgr_array[i].head, mRosMemoryListEntryType, mgrp->mgr_array[i].max_memory_num, mgrp->mgr_array[i].memory_entries);
	}
	return MROS_E_OK;
}

mRosReturnType mros_mem_alloc(mRosMemoryManagerType *mgrp, mRosSizeType size, mRosMemoryListEntryType **memory)
{
	if (memory == NULL) {
		return MROS_E_INVAL;
	}
	for (mros_uint32 i = 0; i < mgrp->mgr_num; i++) {
		if (size > mgrp->mgr_array[i].memsize) {
			continue;
		}
		if (mgrp->mgr_array[i].head.free_num <= 0) {
			continue;
		}
		ListEntry_Alloc(&mgrp->mgr_array[i].head, mRosMemoryListEntryType, memory);
		(*memory)->data.size = size;
		return MROS_E_OK;
	}
	return MROS_E_NOMEM;
}

mRosReturnType mros_mem_free(mRosMemoryManagerType *mgrp, mRosMemoryListEntryType *memory)
{
	if (memory == NULL) {
		return MROS_E_OK;
	}
	if (memory->data.header_id >= mgrp->mgr_num) {
		return MROS_E_INVAL;
	}
	if (memory->data.memory_id > mgrp->mgr_array[memory->data.header_id].max_memory_num) {
		return MROS_E_RANGE;
	}
	memory->data.size = 0;
	ListEntry_Free(&mgrp->mgr_array[memory->data.header_id].head, memory);
	return MROS_E_OK;
}

