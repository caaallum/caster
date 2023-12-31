#include "resource_manager.h"
#include "io.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "map.h"
#include <stdio.h>
#include <cJSON.h>

static map_t *shaders;
static map_t *textures;
static map_t *levels;

void
rm_init(void) {
    shaders = map_new();
    textures = map_new();
    levels = map_new();
}

void
rm_destroy(void) {
    map_destroy(shaders);
    map_destroy(textures);
    map_destroy(levels);
}

static shader_t *
rm_load_shader_from_file(const char *vertex_file, const char *fragment_file, const char *geometry_file) {
    char *vertex_code;
    char *fragment_code;
    char *geometry_code;

    if (io_read_file(vertex_file, &vertex_code) != 0) {
        fprintf(stderr, "ERROR::SHADER: Failed to read shader file %s\n", vertex_file);
    }
    if (io_read_file(fragment_file, &fragment_code) != 0) {
        fprintf(stderr, "ERROR::SHADER: Failed to read shader file %s\n", fragment_file);
    }
    if (geometry_file != NULL) {
        if (io_read_file(geometry_file, &geometry_code) != 0) {
            fprintf(stderr, "ERROR::SHADER: Failed to read shader file %s\n", geometry_file);
        }
    }

    shader_t *shader = shader_new();
    shader_compile(shader, vertex_code, fragment_code, geometry_file != NULL ? geometry_code : NULL);

    if (vertex_code) {
        free(vertex_code);
    }
    if (fragment_code) {
        free(fragment_code);
    }
    if (geometry_file != NULL) {
        free(geometry_code);
    }

    return shader;
}

shader_t *
rm_load_shader(const char *vertex_file, const char *fragment_file, const char *geometry_file, const char *name) {
    shader_t *shader = rm_load_shader_from_file(vertex_file, fragment_file, geometry_file);
    map_add(shaders, name, shader);

    return map_get(shaders, name);
}

static texture2d_t *
rm_load_texture_from_file(const char *file, bool alpha) {
    texture2d_t *texture = texture2d_new();
    int width;
    int height;
    int nr_channels;

    if (alpha) {
        texture->internal_format = GL_RGBA;
        texture->image_format = GL_RGBA;
    }

    unsigned char *data = stbi_load(file, &width, &height, &nr_channels, 0);
    texture2d_generate(texture, width, height, data);

    stbi_image_free(data);
    return texture;
}

texture2d_t *
rm_load_texture(const char *file, bool alpha, const char *name) {
    texture2d_t *texture = rm_load_texture_from_file(file, alpha);
    map_add(textures, name, texture);

    return map_get(textures, name);
}

static level_t *
rm_load_level_from_file(const char *file) {
    level_t *level = level_new();
    const cJSON *map = NULL;
    cJSON *mapi = NULL;
    const cJSON *width = NULL;
    const cJSON *height = NULL;
    char *file_data = NULL;

    io_read_file(file, &file_data);

    cJSON *json = cJSON_Parse(file_data);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        goto end;
    }

    width = cJSON_GetObjectItem(json, "width");
    if (cJSON_IsNumber(width)) {
        level->map.w = width->valueint;
    }

    height = cJSON_GetObjectItem(json, "height");
    if (cJSON_IsNumber(height)) {
        level->map.h = height->valueint;
    }

    map = cJSON_GetObjectItem(json, "map");
    cJSON_ArrayForEach(mapi, map) {
        vector_pushback(level->map.d, &mapi->valueint, sizeof(int));
    }
end:
    cJSON_Delete(json);
    if (file_data) {
        free(file_data);
    }
    return level;
}

level_t *
rm_load_level(const char *file, const char *name) {
    level_t *level = rm_load_level_from_file(file);
    map_add(levels, name, level);

    return map_get(levels, name);
}

shader_t *
rm_get_shader(const char *name) {
    return map_get(shaders, name);
}

texture2d_t *
rm_get_texture(const char *name) {
    return map_get(textures, name);
}

level_t *
rm_get_level(const char *name) {
    return map_get(levels, name);
}

