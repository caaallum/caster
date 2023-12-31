#ifndef __GAME_H
#define __GAME_H

#include "level.h"

typedef struct _game_t game_t;

struct _game_t {
    int keys[1024];

    struct {
        unsigned int width;
        unsigned int height;
    } window;

    level_t *level;

    void (*process_input)(game_t *this, float dr);
    void (*update)(game_t *this, float dt);
    void (*render)(game_t *this);
    void (*destroy)(game_t *this);
};

game_t *game_new(unsigned int width, unsigned int height);

#endif /* __GAME_H */
