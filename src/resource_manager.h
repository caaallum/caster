#ifndef __RESOURCE_MANAGER_H
#define __RESOURCE_MANAGER_H

#include "map.h"
#include "texture2d.h"
#include "shader.h"

void rm_init(void);

void rm_destroy(void);

shader_t *rm_load_shader(const char *vertex_file, const char *fragment_file, const char *geometry_file, const char *name);

texture2d_t *rm_load_texture(const char *file, bool alpha, const char *name);

shader_t *rm_get_shader(const char *name);

texture2d_t *rm_get_texture(const char *name);

#endif /* __RESOURCE_MANAGER_H */
