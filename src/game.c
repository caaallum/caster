#include "game.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "resource_manager.h"

static void 
game_init(game_t *game) {
    
    /* Load shaders */
    rm_load_shader("assets/shaders/line.vs", "assets/shaders/line.frag", NULL, "line");
    mat4 projection;
    glm_ortho(0.0f, game->window.width, game->window.height, 0.0f, -1.0f, 1.0f, projection);
    shader_t *line_shader = rm_get_shader("line");
    shader_use(line_shader);
    shader_set_matrix4(line_shader, "projection", projection);
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
