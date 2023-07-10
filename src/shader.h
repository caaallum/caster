#ifndef __SHADER_H
#define __SHADER_H

#include <glm/glm.hpp>

class Shader {
public:
    Shader();
    ~Shader();
    
    Shader& compile(const char *vertex_source, const char *fragment_source, const char *geometry_source = nullptr);
    Shader& use();

    Shader& setFloat(const char *name, float value);

    Shader& setInt(const char *name, int value);

    Shader& setVector2(const char *name, float x, float y);
    Shader& setVector2(const char *name, glm::vec2 value);

    Shader& setVector3(const char *name, float x, float y, float z);
    Shader& setVector3(const char *name, glm::vec3 value);

    Shader& setVector4(const char *name, float x, float y, float z, float w);
    Shader& setVector4(const char *name, glm::vec4 value);

    Shader& setMat4(const char *name, glm::mat4 value);

private:
    unsigned int ID;
};

#endif /* __SHADER_H */
