#include "texture2d.h"

#include <glad/glad.h>
#include <stdlib.h>
#include <assert.h>

texture2d_t *
texture2d_new(void) {
    texture2d_t *texture = malloc(sizeof(texture2d_t));
    assert(texture);

    texture->width = 0;
    texture->height = 0;
    texture->internal_format = GL_RGB;
    texture->image_format = GL_RGB;
    texture->wrap_s = GL_REPEAT;
    texture->wrap_t = GL_REPEAT;
    texture->filter_min = GL_LINEAR;
    texture->filter_max = GL_LINEAR;

    glGenTextures(1, &texture->ID);

    return texture;
}

void 
texture2d_destroy(texture2d_t *texture) {
    free(texture);
}

void
texture2d_generate(texture2d_t *texture, unsigned int width, unsigned int height, unsigned char *data) {
    texture->width = width;
    texture->height = height;

    /* Create texture */
    glBindTexture(GL_TEXTURE_2D, texture->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, texture->internal_format, width, height, 0, texture->image_format, GL_UNSIGNED_BYTE, data);

    /* Set texture wrap and filter modes */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->filter_max);

    /* Unbind texture */
    glBindTexture(GL_TEXTURE_2D, 0);
}

void
texture2d_bind(texture2d_t *texture) {
    glBindTexture(GL_TEXTURE_2D, texture->ID);
}
