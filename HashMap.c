//
// Created by Yotam Levit on 21/05/2024.
//

#include "HashMap.h"


#define HASH_PRIME 1099511628211UL


/* Simple hash function for strings */
size_t defaultHashFunction(void *key) {
    char *str = (char *)key;
    char* ch;
    size_t hash = 0;
    for (ch = str; *ch; ch++) {
        hash ^= (size_t)(unsigned char)(*ch);
        hash *= HASH_PRIME;
    }

    return hash;
}


/* Compare function for strings */
int defaultKeyCompareFunction(void *key1, void *key2) {
    return strcmp((char *)key1, (char *)key2);
}


HashMapPtr createHashMap(size_t bucketCount, size_t (*hashFunction)(void *), int (*keyCompareFunction)(void *, void *)) {
    HashMapPtr map = (HashMapPtr)malloc(sizeof(HashMap));
    if(!map)
        return NULL;

    map->entries = (HashMapEntryPtr *)calloc(bucketCount, sizeof(HashMapEntryPtr));
    if(!map->entries){
        free(map);
        return NULL;
    }

    map->bucketCount = bucketCount;
    map->hashFunction = hashFunction ? hashFunction : defaultHashFunction;
    map->keyCompareFunction = keyCompareFunction ? keyCompareFunction : defaultKeyCompareFunction;
    return map;
}

/* Insert an element into the hash map */
void hashMapInsert(HashMapPtr map, void *key, void *value) {
    size_t bucket_index = map->hashFunction(key) % map->bucketCount;
    HashMapEntry *entry = map->entries[bucket_index];

    while (entry != NULL) {
        if (map->keyCompareFunction(entry->key, key) == 0) {
            entry->value = value;
            return;
        }
        entry = entry->next;
    }

    entry = (HashMapEntry *)malloc(sizeof(HashMapEntry));
    entry->key = key;
    entry->value = value;
    entry->next = map->entries[bucket_index];
    map->entries[bucket_index] = entry;
}


/* Find an element in the hash map */
void *hashMapFind(HashMapPtr map, void *key) {
    size_t bucket_index = map->hashFunction(key) % map->bucketCount;
    HashMapEntry *entry = map->entries[bucket_index];

    while (entry != NULL) {
        if (map->keyCompareFunction(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL;
}

/* Free the hash map */
void hashMapFree(HashMapPtr map) {
    for (size_t i = 0; i < map->bucketCount; i++) {
        HashMapEntry *entry = map->entries[i];
        while (entry != NULL) {
            HashMapEntry *next = entry->next;
            free(entry);
            entry = next;
        }
    }
    free(map->entries);
    free(map);
}
