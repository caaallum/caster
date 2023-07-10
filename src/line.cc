#include "line.h"
#include "resource_manager.h"
#include <glad/glad.h>

void
line_draw(vec2 start, vec2 end) {
    GLfloat vertices[] = {
        start[0], start[1], 0,
        end[0], end[1], 0
    };
    
    unsigned int VAO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    shader_t *shader = rm_get_shader("line");
    shader_use(shader);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 9, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    
    shader_set_vector3f(shader, "color", (vec3){1.0, 0.0, 0.0});

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
}
