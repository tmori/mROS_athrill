#ifndef _MROS_MEMORY_H_
#define _MROS_MEMORY_H_

#include "mros_types.h"
#include "mros_list.h"

namespace mros {
namespace memory {

typedef enum {
	MROS_MEMSIZE_16B = 0,
	MROS_MEMSIZE_32B,
	MROS_MEMSIZE_64B,
	MROS_MEMSIZE_128B,
	MROS_MEMSIZE_256B,
	MROS_MEMSIZE_512B,
	MROS_MEMSIZE_1KB,
	MROS_MEMSIZE_2KB,
	MROS_MEMSIZE_4KB,
	MROS_MEMSIZE_8KB,
	MROS_MEMSIZE_NUM,
} mRosMemorySizeIdType;

typedef struct {
	mRosMemorySizeIdType	memsize_id;
	mRosIdType				memory_id;
	mRosSizeType			memsize;
	mRosSizeType			size;
	char 					*memp;
} mRosMemoryEntryType;

typedef ListEntryType(mRosMemoryListEntryType, mRosMemoryEntryType) mRosMemoryListEntryType;
typedef ListHeadType(mRosMemoryListEntryType) mRosMemoryListHeadType;

typedef struct {
	mRosMemoryListHeadType head;
	mRosSizeType max_memory_num;
	mRosMemoryListEntryType *memory_entries;
	char					*memory;
} mRosMemoryManagerType;

class mRosMemory {
public:
	mRosMemory();
	~mRosMemory();

	mRosReturnType init(mRosSizeType preallocation_count[MROS_MEMSIZE_NUM]);
	mRosReturnType memory_alloc(mRosSizeType size, mRosMemoryListEntryType **memory);
	mRosReturnType memory_free(mRosMemoryListEntryType &memory);

private:
	mRosMemoryManagerType memory_manager[MROS_MEMSIZE_NUM];
};

}
}

#endif /* _MROS_MEMORY_H_ */
