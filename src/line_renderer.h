#ifndef __LINE_RENDERER_H
#define __LINE_RENDERER_H

#include "shader.h"
#include <cglm/cglm.h>

typedef struct {
    shader_t *shader;
    unsigned int quad_vao;
} line_renderer_t;

#endif /* __LINE_RENDERER_H */
