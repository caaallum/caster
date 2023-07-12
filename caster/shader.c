#include "shader.h"
#include <glad/glad.h>
#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

shader_t *
shader_new(void) {
    shader_t *shader = malloc(sizeof(shader_t));
    assert(shader);

    return shader;
}

void
shader_destroy(shader_t *shader) {
    free(shader);
}

void
shader_use(shader_t *shader) {
    glUseProgram(shader->ID);
}

void
shader_compile(shader_t *shader, const char *vertex_source, const char *fragment_source, const char *geometry_source) {
    unsigned int vertex;
    unsigned int fragment;
    unsigned int geometry;

    /* Vertex shader */
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_source, NULL);
    glCompileShader(vertex);
    shader_check_compile_errors(shader, vertex, "VERTEX");

    /* Fragment shader */
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_source, NULL);
    glCompileShader(fragment);
    shader_check_compile_errors(shader, fragment, "FRAGMENT");

    /* Geometry shader */
    if (geometry_source != NULL) {
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &geometry_source, NULL);
        glCompileShader(geometry);
        shader_check_compile_errors(shader, geometry, "GEOMETRY");
    }

    /* Create shader program */
    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, vertex);
    glAttachShader(shader->ID, fragment);
    if (geometry_source != NULL) {
        glAttachShader(shader->ID, geometry);
    }
    glLinkProgram(shader->ID);
    shader_check_compile_errors(shader, shader->ID, "PROGRAM");

    /* Cleanup */
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometry_source != NULL) {
        glDeleteShader(geometry);
    }
}

void
shader_set_float(shader_t *shader, const char *name, float value, bool use_shader) {
    if (use_shader) {
        shader_use(shader);
    }
    glUniform1f(glGetUniformLocation(shader->ID, name), value);
}

void
shader_set_integer(shader_t *shader, const char *name, int value, bool use_shader) {
    if (use_shader) {
        shader_use(shader);
    }
    glUniform1i(glGetUniformLocation(shader->ID, name), value);
}

void
shader_set_vector2pf(shader_t *shader, const char *name, float x, float y, bool use_shader) {
    if (use_shader) {
        shader_use(shader);
    }
    glUniform2f(glGetUniformLocation(shader->ID, name), x, y);
}

void
shader_set_vector2f(shader_t *shader, const char *name, vec2 value, bool use_shader) {
    if (use_shader) {
        shader_use(shader);
    }
    glUniform2f(glGetUniformLocation(shader->ID, name), value[0], value[1]);
}

void
shader_set_vector3pf(shader_t *shader, const char *name, float x, float y, float z, bool use_shader) {
    if (use_shader) {
        shader_use(shader);
    }
    glUniform3f(glGetUniformLocation(shader->ID, name), x, y, z);
}

void
shader_set_vector3f(shader_t *shader, const char *name, vec3 value, bool use_shader) {
    if (use_shader) {
        shader_use(shader);
    }
    glUniform3f(glGetUniformLocation(shader->ID, name), value[0], value[1], value[2]);
}

void
shader_set_vector4pf(shader_t *shader, const char *name, float x, float y, float z, float w, bool use_shader) {
    if (use_shader) {
        shader_use(shader);
    }
    glUniform4f(glGetUniformLocation(shader->ID, name), x, y, z, w);
}

void
shader_set_vector4f(shader_t *shader, const char *name, vec4 value, bool use_shader) {
    if (use_shader) {
        shader_use(shader);
    }
    glUniform4f(glGetUniformLocation(shader->ID, name), value[0], value[1], value[2], value[3]);
}

void
shader_set_matrix4(shader_t *shader, const char *name, mat4 matrix, bool use_shader) {
    if (use_shader) {
        shader_use(shader);
    }
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, name), 1, GL_FALSE, (const float *)&matrix[0][0]);
}

void
shader_check_compile_errors(shader_t *shader, unsigned int object, const char *type) {
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
