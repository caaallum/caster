#include "game.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "resource_manager.h"

#include <GLFW/glfw3.h>

static void game_init(game_t *game) {
}

void game_destroy(game_t *game) { 
    free(game); 
}

void game_process_input(game_t *game, float dt) {
}

void game_update(game_t *game, float dt) {
}

void game_render(game_t *game) {
}

game_t *
game_new(unsigned int width, unsigned int height) {
    game_t *game = malloc(sizeof(game_t));
    assert(game);
    game->window.width = width;
    game->window.height = height;
    memset(game->keys, 0, 1024);
    
    game->process_input = game_process_input;
    game->update = game_update;
    game->render = game_render;
    game->destroy = game_destroy;

    game_init(game);

    return game;
}


