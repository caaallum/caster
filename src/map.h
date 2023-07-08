#ifndef __MAP_H
#define __MAP_H

typedef struct map_t map_t;

/**********************************************************
 * \brief Init new map
 *
 * \returns newly created map
 **********************************************************/
map_t *map_new(void);

/**********************************************************
 * \brief Free map memory
 *
 * \param map this
 **********************************************************/
void map_destroy(map_t *map);

/**********************************************************
 * \brief Get total of items in map
 *
 * \param map this
 *
 * \returns int total
 **********************************************************/
int map_total(const map_t *map);

/**********************************************************
 * \brief Add item to map
 * 
 * \param map this
 * \param key map key
 * \param val map value
 **********************************************************/
void map_add(map_t *const map, const char *const key, void *val);

/**********************************************************
 * \brief Add item to map and copy value
 * 
 * \param map  this
 * \param key  map key
 * \param val  map value
 * \param size size size of value
 **********************************************************/
void map_pushback(map_t *const map, const char *const key, void *val, int size);

/**********************************************************
 * \brief Get item from map
 * 
 * \param map this
 * \param key map key
 *
 * \returns item if valid key, NULL if not
 **********************************************************/
void *map_get(const map_t *map, const char *const key);

#endif /* __MAP_H */
