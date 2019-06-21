#include "mros_memory.h"
#include <stdio.h>

#define MEM_CONFIG_NUM	3

MROS_MEMORY_CONFIG_DECLARE_ENTRY(test_memory_entry1, 10, 4);
MROS_MEMORY_CONFIG_DECLARE_ENTRY(test_memory_entry2, 10, 8);
MROS_MEMORY_CONFIG_DECLARE_ENTRY(test_memory_entry3, 10, 16);

static mRosMemoryConfigType *config[MEM_CONFIG_NUM] = {
		&test_memory_entry1_config,
		&test_memory_entry2_config,
		&test_memory_entry3_config,
};

MROS_MEMORY_CONFIG_DECLARE_MANAGER(mgr, MEM_CONFIG_NUM);

int main(int argc, const char* argv[])
{
	mRosReturnType ret;
	mRosMemoryListEntryType *entry;

	ret = mros_mem_init(MEM_CONFIG_NUM, config, &mgr);
	printf("ret=%d\n", ret);

	ret = mros_mem_alloc(&mgr, 5, &entry);
	printf("ret=%d\n", ret);
	printf("entry=0x%p\n", entry);
	printf("memory_id=0x%x\n", entry->data.memory_id);
	printf("memsize=0x%x\n", entry->data.memsize);
	printf("header_id=0x%x\n", entry->data.header_id);
	printf("size=0x%x\n", entry->data.size);
	ret = mros_mem_free(&mgr, entry);
	printf("ret=%d\n", ret);

	return 0;
}
