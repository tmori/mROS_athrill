#include "primitive_container.h"
#include <stdlib.h>

using namespace mros::lib;

template <typename T>
PrimitiveContainer<T>::PrimitiveContainer(mros_uint32 size)
{
	this->array_size = size;
	this->usecount = 0;
	this->array = (T *)malloc(size * sizeof(T));
	//TODO ASSERT
}

template <typename T>
PrimitiveContainer<T>::~PrimitiveContainer()
{
	if (this->array != NULL) {
		free(this->array);
		this->array = NULL;
	}
	this->usecount = 0;
	this->array_size = 0;
}
