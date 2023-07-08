#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vector2.h"
#include <math.h>
#include "resource_manager.h"
#include "line.h"
#include "game.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int world_map[MAP_WIDTH][MAP_HEIGHT] = {
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Caster", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    rm_init();
    game_t *game = game_new(SCREEN_WIDTH, SCREEN_HEIGHT);

    vector2d_t pos = {22, 12};
    vector2d_t dir = {-1, 0};
    vector2d_t plane = {0, 0.66};

    double time = 0;
    double old_time = 0;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int x = 0; x < SCREEN_WIDTH; x++) {
            double camera = 2 * x / (double)SCREEN_WIDTH - 1;
            vector2d_t ray_dir = {
                dir.x + plane.x * camera,
                dir.y + plane.y * camera
            };

            vector2i_t map = {(int)pos.x, (int)pos.y};
            vector2d_t side_dist = {0, 0};

            vector2d_t delta_dist = {
                (ray_dir.x == 0) ? 1e30 : fabs(1 / ray_dir.x),
                (ray_dir.y == 0) ? 1e30 : fabs(1 / ray_dir.y)
            };
            double perp_wall_dist;

            vector2i_t step;

            int hit = 0;
            int side;

            if (ray_dir.x < 0) {
                step.x = -1;
                side_dist.x = (pos.x - map.x) * delta_dist.x;
            } else {
                step.x = 1;
                side_dist.x = (map.x + 1.0 - pos.x) * delta_dist.x;
            }
            if (ray_dir.y < 0) {
                step.y = -1;
                side_dist.y = (pos.y - map.y) * delta_dist.y;
            } else {
                step.y = 1;
                side_dist.y = (map.y + 1.0 - pos.y) * delta_dist.y;
            }

            while (hit == 0) {
                if (side_dist.x < side_dist.y) {
                    side_dist.x += delta_dist.x;
                    map.x += step.x;
                    side = 0;
                } else {
                    side_dist.y += delta_dist.y;
                    map.y += step.y;
                    side = 1;
                }
                if (world_map[map.x][map.y] > 0) hit = 1;
            }

            if (side == 0) {
                perp_wall_dist = (side_dist.x - delta_dist.x);
            } else {
                perp_wall_dist = (side_dist.y - delta_dist.y);
            }

            int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

            int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
            if (draw_start < 0) {
                draw_start = 0;
            }
            int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
            if (draw_end >= SCREEN_HEIGHT) {
                draw_end = SCREEN_HEIGHT - 1;
            }

            line_draw((vec2){x, draw_start}, (vec2){x, draw_end});
        }
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    rm_destroy();

    return 0;
}

void
key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void
framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
