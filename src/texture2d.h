#ifndef __TEXTURE2D_H
#define __TEXTURE2D_H

class Texture2d {
public:
    Texture2d();
    ~Texture2d();

    void bind();

    void generate(unsigned int width, unsigned int height, unsigned char *data);

private:
    unsigned int ID;
public:
    unsigned int width;
    unsigned int height;
    unsigned int internal_format;
    unsigned int image_format;
    unsigned int wrap_s;
    unsigned int wrap_t;
    unsigned int filter_min;
    unsigned int filter_max;
};

#endif /* __TEXTURE2D_H */
