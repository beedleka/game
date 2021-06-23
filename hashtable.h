#pragma once

#include "types.h"

#include <stdlib.h>
#include <string.h>

typedef struct HtEntry{
    const char* key;
    void* value;
} HtEntry;

typedef struct Ht{
    HtEntry* entries;
    size_t capacity;
    size_t length;
} Ht;

typedef struct Hti{
    const char* key;
    void* value;
    Ht* hashtable;
    size_t index;
} Hti;

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
#define INITIAL_CAPACITY 16

Ht* ht_create();
void ht_destroy(Ht* hashtable);
void* ht_get(Ht* hashtable, const char* key);
const char* ht_set_entry(HtEntry* entries, size_t capacity, size_t* length, const char* key, void* value);
const char* ht_set(Ht* hashtable, const char* key, void* value);
u8 ht_expand(Ht* hashtable);
Hti ht_iter(Ht* hashtable);
u8 ht_next(Hti* iterator);
u64 fnv1_hash(const char* s);