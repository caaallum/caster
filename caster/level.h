#ifndef __LEVEL_H
#define __LEVEL_H 

#include <cglm/cglm.h>
#include "vector.h"

typedef struct _level_t level_t;

struct _level_t {
    vec2 pos;
    vec2 dir;
    vec2 plane;

    struct {
        unsigned int w;
        unsigned int h;
        vector_t *d;
    } map;

    void (*draw)(level_t *this, float dt);
    void (*update)(level_t *this, float dt);
};

level_t *level_new(void);

#endif /* __LEVEL_H */
