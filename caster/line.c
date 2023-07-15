#include "line.h"
#include "cglm/mat4.h"
#include "resource_manager.h"
#include <glad/glad.h>
#include "game.h"

extern game_t *game;

void line_draw(vec2 start, vec2 end, vec3 color) {
    float x1 = 2 * start[0] / game->window.width - 1;
    float y1 = 2 * start[1] / game->window.height - 1;
    float x2 = 2 * end[0] / game->window.width - 1;
    float y2 = 2 * end[1] / game->window.height - 1;
    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    shader_t *shader = rm_get_shader("line");
    unsigned int VAO, VBO;

    float vertices[] = {
        x1, y1, 0,
        x2, y2, 0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    shader_use(shader);
    shader_set_vector3f(shader, "color", color, false);
    shader_set_matrix4(shader, "projection", projection, false);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 6, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glDeleteVertexArrays(1, &VAO); 
}
