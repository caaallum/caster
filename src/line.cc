#include "line.h"
#include "resource_manager.h"
#include <glad/glad.h>
#include "game.h"

extern Game game;

void
line_draw(glm::vec2 start, glm::vec2 end, glm::vec3 color) {
    float x1 = 2 * start.x / game.width - 1;
    float y1 = 2 * start.y / game.height - 1;
    float x2 = 2 * end.x / game.width - 1;
    float y2 = 2 * end.y / game.height - 1;

    GLfloat vertices[] = {
        x1, y1, 0,
        x2, y2, 0
    };
    
    unsigned int VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    ResourceManager::GetShader("line").use().setVector3("color", color).setMat4("projection", glm::mat4(1.0));

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 6, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glDeleteVertexArrays(1, &VAO);
}
