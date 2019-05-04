#ifndef _PRIMITIVE_CONTAINER_H_
#define _PRIMITIVE_CONTAINER_H_

#include "mros_types.h"

namespace mros {
namespace lib {

template <typename T>
class PrimitiveContainer {
public:
	PrimitiveContainer(mros_uint32 size);
	~PrimitiveContainer();

	mRosSizeType size()
	{
		return array_size;
	}

	T get(mRosIdType index) const
	{
		if (index < array_size) {
			return array[index];
		}
		else {
			return array[array_size - 1];
		}
	}
	T operator [] (mRosIdType index) const
	{
		return get(index);
	}

	T& operator [] (mRosIdType index)
	{
		if (index < array_size) {
			return array[index];
		}
		else {
			return array[array_size - 1];
		}
	}

	void put(mRosIdType index, T value)
	{
		if (index < array_size) {
			array[index] = value;
		}
		else {
			/* nothing to do */
		}
	}


private:
	mros_uint32 usecount;
	mros_uint32	array_size;
	T 			*array;
};

}
}

#include "primitive_container_impl.h"

#endif /* _PRIMITIVE_CONTAINER_H_ */
