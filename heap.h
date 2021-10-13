#pragma once

#include "types.h"

typedef struct Heap{
	u32 capacity;
	u32 count;
} Heap;

u32 heap_get_left_child_index(u32 parent_index);
u32 heap_get_right_child_index(u32 parent_index);
u32 heap_get_parent_index(u32 child_index);