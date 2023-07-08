#include "game.h"

#include "resource_manager.h"

#include <stdlib.h>
#include <assert.h>

static void 
game_init(game_t *game) {
    
    /* Load shaders */
    rm_load_shader("assets/shaders/line.vs", "assets/shaders/line.frag", NULL, "line");
}

game_t *
game_new(unsigned int width, unsigned int height) {
    game_t *game = malloc(sizeof(game_t));
    assert(game);

    game->window.width = width;
    game->window.height = height;
    memset(game->keys, 0, 1024);

    game_init(game);

    return game;
}
