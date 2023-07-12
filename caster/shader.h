#ifndef __SHADER_H
#define __SHADER_H

#include <stdbool.h>
#include <cglm/cglm.h>

typedef struct {
    unsigned int ID;
} shader_t;

shader_t *shader_new(void);

void shader_destroy(shader_t *shader);

void shader_use(shader_t *shader);

void shader_compile(shader_t *shader, const char *vertex_source, const char *fragment_source, const char *geometry_source);

void shader_set_float(shader_t *shader, const char *name, float value, bool use_shader);

void shader_set_integer(shader_t *shader, const char *name, int value, bool use_shader);

void shader_set_vector2pf(shader_t *shader, const char *name, float x, float y, bool use_shader);

void shader_set_vector2f(shader_t *shader, const char *name, vec2 value, bool use_shader);

void shader_set_vector3pf(shader_t *shader, const char *name, float x, float y, float z, bool use_shader);

void shader_set_vector3f(shader_t *shader, const char *name, vec3 value, bool use_shader);

void shader_set_vector4pf(shader_t *shader, const char *name, float x, float y, float z, float w, bool use_shader);

void shader_set_vector4f(shader_t *shader, const char *name, vec4 value, bool use_shader);

void shader_set_matrix4(shader_t *shader, const char *name, mat4 matrix, bool use_shader);

void shader_check_compile_errors(shader_t *shader, unsigned int object, const char *type);

#endif /* __SHADER_H */
