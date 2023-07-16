#include "level.h"
#include <stdlib.h>
#include <assert.h>
#include "game.h"
#include <math.h>
#include "line.h"
#include <GLFW/glfw3.h>

extern game_t *game;

static void
draw(level_t *this) {
    for (int x = 0; x < game->window.width; x++) {
        double camera = 2 * x / (double)game->window.width - 1;
        vec2 ray_dir = {
            this->dir[0] + this->plane[0] * camera,
            this->dir[1] + this->plane[1] * camera
        };
        
        ivec2 map = {
            (int)this->pos[0],
            (int)this->pos[1]
        };
        vec2 side_dist = GLM_VEC2_ZERO_INIT;

        vec2 delta_dist = {
            (ray_dir[0] == 0) ? 1e30 : fabs(1 / ray_dir[0]),
            (ray_dir[0] == 0) ? 1e30 : fabs(1 / ray_dir[1])
        };
        double perp_wall_dist;

        ivec2 step;

        int hit = 0;
        int side;

        if (ray_dir[0] < 0) {
            step[0] = -1;
            side_dist[0] = (this->pos[0] - map[0]) * delta_dist[0];
        } else {
            step[0] = 1;
            side_dist[0] = (map[0] + 1.0 - this->pos[0]) * delta_dist[0];
        }
        if (ray_dir[1] < 0) {
            step[1] = -1;
            side_dist[1] = (this->pos[1] - map[1]) * delta_dist[1];
        } else {
            step[1] = 1;
            side_dist[1] = (map[1] + 1.0 - this->pos[1]) * delta_dist[1];
        }

        while (hit == 0) {
            if (side_dist[0] < side_dist[1]) {
                side_dist[0] += delta_dist[0];
                map[0] += step[0];
                side = 0;
            } else {
                side_dist[1] += delta_dist[1];
                map[1] += step[1];
                side = 1;
            }
            if (*(int *)vector_get(this->map.d, map[0] * this->map.w + map[1]) > 0) {
                hit = 1;
            }
        }

        if (side == 0) {
            perp_wall_dist = (side_dist[0] - delta_dist[0]);
        } else {
            perp_wall_dist = (side_dist[1] - delta_dist[1]);
        }

        int line_height = (int)(game->window.height / perp_wall_dist);

        int draw_start = -line_height / 2 + game->window.height / 2;
        if (draw_start < 0) {
            draw_start = 0;
        }

        int draw_end = line_height / 2 + game->window.height / 2;
        if (draw_end >= game->window.height) {
            draw_end = game->window.height - 1;
        }

        vec3 color;
        switch (*(int *)vector_get(this->map.d, map[0] * this->map.w + map[1])) {
            case 1: glm_vec3_copy((vec3){1, 0, 0}, color); break;
            case 2: glm_vec3_copy((vec3){0, 1, 0}, color); break;
            case 3: glm_vec3_copy((vec3){0, 0, 1}, color); break;
            case 4: glm_vec3_copy((vec3){1, 1, 1}, color); break;
            default: glm_vec3_copy((vec3){1, 1, 0}, color); break;
        }

        if (side == 1) {
            color[0] /= 2;
            color[1] /= 2;
            color[2] /= 2;
        }
        line_draw((vec2){x, draw_start}, (vec2){x, draw_end}, color);
    }
}

static void
update(level_t *this, float dt) {
    double move_speed = dt * 5.0;
    double rot_speed = dt * 3.0;

    if (game->keys[GLFW_KEY_UP] || game->keys[GLFW_KEY_W]) {
        if (*(int *)vector_get(this->map.d, ((int)(this->pos[0] + this->dir[0] * move_speed)) * this->map.w + (int)this->pos[1]) == 0) {
            this->pos[0] += this->dir[0] * move_speed;
        }
        if (*(int *)vector_get(this->map.d, (int)this->pos[0] * this->map.w + ((int)(this->pos[1] + this->dir[1] * move_speed))) == 0) {
            this->pos[1] += this->dir[1] * move_speed;
        }
    }

    if (game->keys[GLFW_KEY_DOWN] || game->keys[GLFW_KEY_S]) {
        if (*(int *)vector_get(this->map.d, ((int)(this->pos[0] - this->dir[0] * move_speed)) * this->map.w + (int)this->pos[1]) == 0) {
            this->pos[0] -= this->dir[0] * move_speed;
        }
        if (*(int *)vector_get(this->map.d, (int)this->pos[0] * this->map.w + ((int)(this->pos[1] - this->dir[1] * move_speed))) == 0) {
            this->pos[1] -= this->dir[1] * move_speed;
        }
    }

    if (game->keys[GLFW_KEY_RIGHT] || game->keys[GLFW_KEY_D]) {
        double old_dir = this->dir[0];
        this->dir[0] = this->dir[0] * cos(-rot_speed) - this->dir[1] * sin(-rot_speed);
        this->dir[1] = old_dir * sin(-rot_speed) + this->dir[1] * cos(rot_speed);

        double old_plane = this->plane[0];
        this->plane[0] = this->plane[0] * cos(-rot_speed) - this->plane[1] * sin(-rot_speed);
        this->plane[1] = old_plane * sin(-rot_speed) + this->plane[1] * cos(-rot_speed);
    }

    if (game->keys[GLFW_KEY_LEFT] || game->keys[GLFW_KEY_A]) {
        double old_dir = this->dir[0];
        this->dir[0] = this->dir[0] * cos(rot_speed) - this->dir[1] * sin(rot_speed);
        this->dir[1] = old_dir * sin(rot_speed) + this->dir[1] * cos(rot_speed);

        double old_plane = this->plane[0];
        this->plane[0] = this->plane[0] * cos(rot_speed) - this->plane[1] * sin(rot_speed);
        this->plane[1] = old_plane * sin(rot_speed) + this->plane[1] * cos(rot_speed);
    }
}

level_t *
level_new(void) {
    level_t *level = malloc(sizeof(level_t));
    assert(level);
    
    level->map.d = vector_new();
    glm_vec2_copy((vec2){22, 12}, level->pos);
    glm_vec2_copy((vec2){-1, 0}, level->dir);
    glm_vec2_copy((vec2){0, 0.66}, level->plane);
    
    level->draw = draw;
    level->update = update;

    return level;
}

