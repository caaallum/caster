#ifndef __LINE_RENDERER_H
#define __LINE_RENDERER_H

#include "shader.h"
#include <cglm/cglm.h>

typedef struct _line_renderer_t line_renderer_t;

struct _line_renderer_t {
    shader_t *shader;
    unsigned int quad_vao;

    void (*destroy)(line_renderer_t *this);
    void (*draw)(line_renderer_t *this, vec2 start, vec2 end);
};

line_renderer_t *line_renderer_new(shader_t *shader);

#endif /* __LINE_RENDERER_H */
