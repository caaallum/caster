#include "line.h"
#include <glad/glad.h>

void
line_draw(vec2 start, vec2 end) {
    GLfloat vertices[] = {
        start[0], start[1], 0,
        end[0], end[1], 0
    };


}
