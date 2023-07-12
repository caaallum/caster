#ifndef __LEVEL_H
#define __LEVEL_H 

#include <cglm/cglm.h>

typedef struct _level_t level_t;

struct _level_t {
    vec2 pos;
    vec2 dir;
    vec2 plane;

    unsigned int width;
    unsigned int height;

    void (*draw)(level_t *this, float dt);
};

#endif /* __LEVEL_H */
