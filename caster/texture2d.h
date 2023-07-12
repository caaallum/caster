#ifndef __TEXTURE2D_H
#define __TEXTURE2D_H

typedef struct {
    unsigned int ID;
    unsigned int width;
    unsigned int height;
    unsigned int internal_format;
    unsigned int image_format;
    unsigned int wrap_s;
    unsigned int wrap_t;
    unsigned int filter_min;
    unsigned int filter_max;
} texture2d_t;

texture2d_t *texture2d_new(void);

void texture2d_destroy(texture2d_t *texture);

void texture2d_generate(texture2d_t *texture, unsigned int width, unsigned int height, unsigned char *data);

void texture2d_bind(texture2d_t *texture);

#endif /* __TEXTURE2D_H */
