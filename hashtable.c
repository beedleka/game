#include "hashtable.h"
#include <stdio.h>

Ht* ht_create(){
    Ht* hashtable = malloc(sizeof(Ht));
    if(hashtable == NULL){
        return NULL;
    }

    hashtable->capacity = INITIAL_CAPACITY;
    hashtable->count = 0;

    hashtable->entries = calloc(INITIAL_CAPACITY, sizeof(HtEntry));
    if(hashtable->entries == NULL){
        free(hashtable);
        return NULL;
    }
    return hashtable;
}

void ht_destroy(Ht* hashtable){
    for(size_t i = 0; i < hashtable->capacity; i++){
        if(hashtable->entries[i].key != NULL){
            free((void*)hashtable->entries[i].key);
        }
    }
    free(hashtable->entries);
    free(hashtable);
}

void* ht_get(Ht* hashtable, const char* key){
    u64 hash = fnv1_hash(key);
    size_t index = (size_t)(hash % (u64)hashtable->capacity);
    while(hashtable->entries[index].key != NULL){
        if(strcmp(key, hashtable->entries[index].key) == 0){
            return hashtable->entries[index].value;
        }
        index++;
        if(index >= hashtable->capacity) index = 0;
    }
    return NULL;
}

const char* ht_set_entry(HtEntry* entries, size_t capacity, size_t* count,
    const char* key, void* value){
    u64 hash = fnv1_hash(key);
    size_t index = (size_t)(hash % (u64)capacity);

    while(entries[index].key != NULL){
        if(strcmp(key, entries[index].key) == 0){
            entries[index].value = value;
            return entries[index].key;
        }
        index++;
        if(index >= capacity) index = 0;
    }

    if(count != NULL){
        char* new_key = malloc(sizeof(char)*(strlen(key)+1));
        strcpy(new_key, key);
        key = new_key;
        if(key == NULL){
            return NULL;
        }
        (*count)++;
    }

    entries[index].key = key;
    entries[index].value = value;
    return key;
}

const char* ht_set(Ht* hashtable, const char* key, void* value){
    if(value == NULL){
        return NULL;
    }

    if(hashtable->count >= hashtable->capacity/2){
        if(!ht_expand(hashtable)) return NULL;
    }

    return ht_set_entry(hashtable->entries, hashtable->capacity, &hashtable->count, key, value);
}

u8 ht_expand(Ht* hashtable){
    size_t new_capacity = hashtable->capacity*2;
    if(new_capacity < hashtable->capacity){
        return 0;
    }
    HtEntry* new_entries = calloc(new_capacity, sizeof(HtEntry));
    if(hashtable->entries == NULL){
        return 0;
    }

    for(size_t i = 0; i < hashtable->capacity; i++){
        HtEntry entry = hashtable->entries[i];
        if(entry.key != NULL){
            ht_set_entry(new_entries, new_capacity, NULL, entry.key, entry.value);
        }
    }

    free(hashtable->entries);
    hashtable->entries = new_entries;
    hashtable->capacity = new_capacity;
    return 1;
}

Hti ht_iter(Ht* hashtable){
    Hti iterator = {0};
    iterator.hashtable = hashtable;
    iterator.index = 0;
    return iterator;
}

u8 ht_next(Hti* iterator){
    Ht* hashtable = iterator->hashtable;
    while(iterator->index < hashtable->capacity){
        size_t i = iterator->index;
        iterator->index++;
        if(hashtable->entries[i].key != NULL){
            iterator->key = hashtable->entries[i].key;
            iterator->value = hashtable->entries[i].value;
            return 1;
        }
    }
    return 0;
}

u64 fnv1_hash(const char* s){
    u64 hash = FNV_OFFSET;
    for(const char* p = s; *p; p++){
        hash ^= (u64)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}
