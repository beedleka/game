#pragma once

#include "types.h"

#include <stddef.h>

typedef struct Heap{
	u32 capacity;
	u32 count;
	void** nodes;
} Heap;

void init_heap_(Heap* h, u32 capacity, size_t type_size, u32(*comparator)(void*, void*));
#define init_heap(h, capacity, type, comparator) init_heap_(h, capacity, sizeof(type), comparator)
u32 heap_get_left_child_index(u32 parent_index);
u32 heap_get_right_child_index(u32 parent_index);
u32 heap_get_parent_index(u32 child_index);
void pop_heap(Heap heap, u32 index);
void push_heap(Heap heap, u32 index);