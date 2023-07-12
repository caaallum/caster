#include "shader.h"
#include <glad/glad.h>
#include <stdio.h>
#include <string.h>

Shader::Shader() {

}

Shader::~Shader() {

}

void
check_compile_errors(unsigned int object, const char *type) {
    int success;
    char info_log[1024];

    if (strcmp(type, "PROGRAM") != 0) {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, info_log);
            fprintf(stderr, "| ERROR::SHADER: Compile-time error: Type: %s\n %s\n -- --------------------------------------------------- --\n", type, info_log);
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, info_log);
            fprintf(stderr, "| ERROR:Shader: Link-time error: Type: %s\n %s\n -- --------------------------------------------------- --\n", type, info_log);
        }
    }
}

Shader&
Shader::compile(const char *vertex_source, const char *fragment_source, const char *geometry_source) {
    unsigned int vertex;
    unsigned int fragment;
    unsigned int geometry;

    /* Vertex shader */
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_source, NULL);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX");

    /* Fragment shader */
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_source, NULL);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT");

    /* Geometry shader */
    if (geometry_source != nullptr) {
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &geometry_source, NULL);
        glCompileShader(geometry);
        check_compile_errors(geometry, "GEOMETRY");
    }

    /* Create shader program */
    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertex);
    glAttachShader(this->ID, fragment);
    if (geometry_source != nullptr) {
        glAttachShader(this->ID, geometry);
    }
    glLinkProgram(this->ID);
    check_compile_errors(this->ID, "PROGRAM");

    /* Cleanup */
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometry_source != nullptr) {
        glDeleteShader(geometry);
    }
    return *this;
}

Shader&
Shader::use() {
    glUseProgram(this->ID);
    return *this;
}

Shader&
Shader::setFloat(const char *name, float value) {
    glUniform1f(glGetUniformLocation(this->ID, name), value);
    return *this;
}

Shader&
Shader::setInt(const char *name, int value) {
    glUniform1i(glGetUniformLocation(this->ID, name), value);
    return *this;
}

Shader&
Shader::setVector2(const char *name, float x, float y) {
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
    return *this;
}

Shader&
Shader::setVector2(const char *name, glm::vec2 value) {
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
    return *this;
}

Shader&
Shader::setVector3(const char *name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
    return *this;
}

Shader&
Shader::setVector3(const char *name, glm::vec3 value) {
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
    return *this;
}

Shader&
Shader::setVector4(const char *name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
    return *this;
}

Shader&
Shader::setVector4(const char *name, glm::vec4 value) {
    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
    return *this;
}

Shader&
Shader::setMat4(const char *name, glm::mat4 value) {
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, (const float *)&value[0][0]);
    return *this;
}


