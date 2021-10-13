#include "heap.h"

u32 heap_get_left_child_index(u32 parent_index){
	return parent_index*2+1;
}

u32 heap_get_right_child_index(u32 parent_index){
	return parent_index*2+2;
}

u32 heap_get_parent_index(u32 child_index){
	return (child_index-1)/2;
}

// u32 heap_has_left_child(u32 parent_index)