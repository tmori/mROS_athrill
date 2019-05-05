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
	char 					*memp;
} mRosMemoryEntryType;

typedef ListEntryType(mRosMemoryListEntryType, mRosMemoryEntryType) mRosMemoryListEntryType;
typedef ListHeadType(mRosMemoryListEntryType) mRosMemoryListHeadType;

class mRosMemory {
public:
	static mRosReturnType init(mRosSizeType preallocation_count[MROS_MEMSIZE_NUM]);
	static mRosReturnType memory_alloc(mRosSizeType size, mRosMemoryEntryType &memory);
	static mRosReturnType memory_free(mRosMemoryEntryType &memory);

private:
	static mRosSizeType max_memory_num[MROS_MEMSIZE_NUM];
	static mRosSizeType unit_memory_size[MROS_MEMSIZE_NUM];

	mRosMemory();
	~mRosMemory();
};

}
}

#endif /* _MROS_MEMORY_H_ */
