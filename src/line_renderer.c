#include "line_renderer.h"
#include <glad/glad.h>
#include <assert.h>

static void
destroy(line_renderer_t *this) {
    glDeleteVertexArrays(1, &this->quad_vao);
    free(this);
}

static void 
draw(line_renderer_t *this, vec2 start, vec2 end) {

}

static void
init(line_renderer_t *this) {

}

line_renderer_t *
line_renderer_new(shader_t *shader) {
    line_renderer_t *renderer = malloc(sizeof(line_renderer_t));
    assert(renderer);

    renderer->shader = shader;
    init(renderer);

    return renderer;
}
