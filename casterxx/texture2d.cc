#include "texture2d.h"

#include <glad/glad.h>
#include <stdlib.h>
#include <assert.h>

Texture2d::Texture2d() :
    width(0),
    height(0),
    internal_format(GL_RGB),
    image_format(GL_RGB),
    wrap_s(GL_REPEAT),
    wrap_t(GL_REPEAT),
    filter_min(GL_LINEAR),
    filter_max(GL_LINEAR) {
    glGenTextures(1, &this->ID);
}

Texture2d::~Texture2d() {

}

void
Texture2d::generate(unsigned int width, unsigned int height, unsigned char *data) {
    this->width = width;
    this->height = height;

    /* Create texture */
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, width, height, 0, this->image_format, GL_UNSIGNED_BYTE, data);

    /* Set texture wrap and filter modes */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);

    /* Unbind texture */
    glBindTexture(GL_TEXTURE_2D, 0);

}

void
Texture2d::bind() {
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

