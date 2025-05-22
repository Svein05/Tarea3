#include "map.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

#define HASH_MAP_CAPACITY 103 // Un número primo ayuda a dispersar las claves

struct Map
{
    int (*is_equal)(void *key1, void *key2);
    unsigned int (*hash_func)(void *key);
    List *buckets[HASH_MAP_CAPACITY];
};

typedef Map Map;

Map *map_create(int (*is_equal)(void *key1, void *key2), unsigned int (*hash_func)(void *key))
{
    Map *newMap = (Map *)malloc(sizeof(Map));
    newMap->is_equal = is_equal;
    newMap->hash_func = hash_func;

    for (int i = 0; i < HASH_MAP_CAPACITY; i++)
    {
        newMap->buckets[i] = list_create();
    }

    return newMap;
}

void map_insert(Map *map, void *key, void *value)
{
    unsigned int index = map->hash_func(key) % HASH_MAP_CAPACITY;

    List *bucket = map->buckets[index];
    for (MapPair *pair = list_first(bucket); pair != NULL; pair = list_next(bucket))
    {
        if (map->is_equal(pair->key, key))
            return;
    }

    MapPair *newPair = (MapPair *)malloc(sizeof(MapPair));
    newPair->key = key;
    newPair->value = value;
    list_pushBack(bucket, newPair);
}

void multimap_insert(Map *map, void *key, void *value)
{
    unsigned int index = map->hash_func(key) % HASH_MAP_CAPACITY;

    List *bucket = map->buckets[index];

    MapPair *newPair = (MapPair *)malloc(sizeof(MapPair));
    newPair->key = key;
    newPair->value = value;
    list_pushBack(bucket, newPair);
}

MapPair *map_search(Map *map, void *key)
{
    unsigned int index = map->hash_func(key) % HASH_MAP_CAPACITY;
    List *bucket = map->buckets[index];

    for (MapPair *pair = list_first(bucket); pair != NULL; pair = list_next(bucket))
    {
        if (map->is_equal(pair->key, key))
            return pair;
    }
    return NULL;
}

MapPair *map_remove(Map *map, void *key)
{
    unsigned int index = map->hash_func(key) % HASH_MAP_CAPACITY;
    List *bucket = map->buckets[index];

    for (MapPair *pair = list_first(bucket); pair != NULL; pair = list_next(bucket))
    {
        if (map->is_equal(pair->key, key))
        {
            list_popCurrent(bucket);
            return pair;
        }
    }
    return NULL;
}

void map_clean(Map *map)
{
    for (int i = 0; i < HASH_MAP_CAPACITY; i++)
    {
        list_clean(map->buckets[i]);
    }
}

// Iterador global (solo permite recorrer todo el mapa completo)
static int current_bucket = 0;

MapPair *map_first(Map *map)
{
    current_bucket = 0;
    while (current_bucket < HASH_MAP_CAPACITY)
    {
        MapPair *pair = list_first(map->buckets[current_bucket]);
        if (pair != NULL)
            return pair;
        current_bucket++;
    }
    return NULL;
}

MapPair *map_next(Map *map)
{
    MapPair *pair = list_next(map->buckets[current_bucket]);
    if (pair != NULL)
        return pair;

    current_bucket++;
    while (current_bucket < HASH_MAP_CAPACITY)
    {
        pair = list_first(map->buckets[current_bucket]);
        if (pair != NULL)
            return pair;
        current_bucket++;
    }
    return NULL;
}