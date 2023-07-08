#include "map.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAP_INIT_CAPACITY 4

typedef struct {
    char *key;
    void *val;
} map_val_t;

struct map_t {
    map_val_t **map;
    int total;
    int capacity;
};

map_t *
map_new(void) {
    map_t *map = malloc(sizeof(map_t));
    assert(map);

    map->capacity = MAP_INIT_CAPACITY;
    map->total = 0;
    map->map = malloc(sizeof(map_val_t *) * map->capacity);
    assert(map->map);

    return map;
}

void
map_destroy(map_t *map) {
    for (int i = 0; i < map->total; i++) {
        map_val_t *val = map->map[i];
        free(val->key);
        free(val);
    }
    free(map->map);
    free(map);
}

int
map_total(const map_t *map) {
    assert(map);
    return map->total;
}

void
map_resize(map_t *const map, int capacity) {
    map_val_t **items = realloc(map->map, sizeof(map_val_t *) * capacity);
    assert(items);

    map->map = items;
    map->capacity = capacity;
}

void
map_add(map_t *const map, const char *const key, void *val) {
    assert(map);

    map_val_t *map_val = malloc(sizeof(map_val_t));
    assert(map_val);

    map_val->key = malloc(sizeof(char) + strlen(key));
    assert(map_val->key);
    strcpy(map_val->key, key);

    map_val->val = val;

    if (map->capacity == map->total) {
        map_resize(map, map->capacity * 2);
    }

    map->map[map->total++] = map_val;
}

void
map_pushback(map_t *const map, const char *const key, void *val, int size) {
    assert(map);
    assert(val);
    assert(size > 0);

    map_val_t *map_val = malloc(sizeof(map_val_t));
    assert(map_val);

    map_val->key = malloc(sizeof(char) + strlen(key));
    assert(map_val->key);
    strcpy(map_val->key, key);

    map_val->val = malloc(sizeof(size));
    memcpy(map_val->val, val, size);

    if (map->capacity == map->total) {
        map_resize(map, map->capacity * 2);
    }

    map->map[map->total++] = map_val;
}

void *
map_get(const map_t *map, const char *const key) {
    assert(map);

    for (int i = 0; i < map->total; i++) {
        map_val_t *val = map->map[i];

        if (strcmp(val->key, key) == 0) {
            return val->val;
        }
    }
    return NULL;
}
