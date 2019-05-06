#include "mros_memory.h"
#include <stdlib.h>

using namespace mros::memory;

static const mRosSizeType memory_size[MROS_MEMSIZE_NUM] = {
	16,
	32,
	64,
	128,
	512,
	1024,
	2048,
	4096,
	8192,
};

#define MEMORY_ID(index)		((index) + 1U)
#define MEMORY_INDEX(id)		((id) - 1U)

#define MEMORY_OBJ(mid, id)		memory_manager[(mid)].memory_entries[MEMORY_INDEX((id))]

mRosReturnType mRosMemory::init(mRosSizeType preallocation_count[MROS_MEMSIZE_NUM])
{
	for (mros_uint32 i = 0; i < MROS_MEMSIZE_NUM; i++) {
		memory_manager[i].max_memory_num = preallocation_count[i];
		if (memory_manager[i].max_memory_num == 0) {
			memory_manager[i].memory_entries = NULL;
			memory_manager[i].memory = NULL;
			List_Init(&memory_manager[i].head, mRosMemoryListEntryType, 0, NULL);
			continue;
		}
		memory_manager[i].memory_entries = (mRosMemoryListEntryType *)malloc(memory_manager[i].max_memory_num * sizeof(mRosMemoryListEntryType));
		//TODO ASSERT
		memory_manager[i].memory = (char *)malloc(memory_manager[i].max_memory_num * memory_size[i]);
		//TODO ASSERT
		for (mros_uint32 j = 0; j < memory_manager[i].max_memory_num; j++) {
			mRosMemoryListEntryType *entry = &(memory_manager[i].memory_entries[j]);
			entry->data.memsize_id = (mRosMemorySizeIdType)i;
			entry->data.memory_id = MEMORY_ID(j);
			entry->data.memsize = memory_size[i];
			entry->data.memp = &(memory_manager[i].memory[(memory_size[i] * j)]);
		}
		List_Init(&memory_manager[i].head, mRosMemoryListEntryType, memory_manager[i].max_memory_num, memory_manager[i].memory_entries);
	}
	return MROS_E_OK;
}
mRosReturnType mRosMemory::memory_alloc(mRosSizeType size, mRosMemoryListEntryType **memory)
{
	for (mros_uint32 i = 0; i < MROS_MEMSIZE_NUM; i++) {
		if (size > memory_size[i]) {
			continue;
		}
		if (memory_manager[i].head.free_num <= 0) {
			continue;
		}
		ListEntry_Alloc(&memory_manager[i].head, mRosMemoryListEntryType, memory);
		return MROS_E_OK;
	}
	return MROS_E_NOMEM;
}

mRosReturnType mRosMemory::memory_free(mRosMemoryListEntryType &memory)
{
	if (memory.data.memsize_id >= MROS_MEMSIZE_NUM) {
		return MROS_E_INVAL;
	}
	if (memory.data.memory_id > memory_manager[memory.data.memsize_id].max_memory_num) {
		return MROS_E_RANGE;
	}
	ListEntry_Free(&memory_manager[memory.data.memsize_id].head, &memory);
	return MROS_E_OK;
}

mRosMemory::mRosMemory()
{
}

mRosMemory::~mRosMemory()
{
	for (mros_uint32 i = 0; i < MROS_MEMSIZE_NUM; i++) {
		if (memory_manager[i].memory_entries != NULL) {
			free(memory_manager[i].memory_entries);
			memory_manager[i].memory_entries = NULL;
		}
		if (memory_manager[i].memory != NULL) {
			free(memory_manager[i].memory);
			memory_manager[i].memory = NULL;
		}
	}
}

