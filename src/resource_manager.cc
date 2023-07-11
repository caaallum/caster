#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::map<std::string, Texture2d> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Map> ResourceManager::maps;

Shader
ResourceManager::LoadShader(const char *vertexFile, const char *fragmentFile, const char *geometryFile, const char *name) {
    shaders[name] = loadShaderFromFile(vertexFile, fragmentFile, geometryFile);
    return shaders[name];
}

Shader
ResourceManager::GetShader(const char *name) {
    return shaders[name];
}

Texture2d
ResourceManager::LoadTexture(const char *file, bool alpha, const char *name) {
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
}

Texture2d
ResourceManager::GetTexture(const char *name) {
    return textures[name];
}

Map
ResourceManager::LoadMap(const char *file, const char *name) {
    maps[name] = loadMapFromFile(file);
    return maps[name];
}

Map
ResourceManager::GetMap(const char *name) {
    return maps[name];
}

Shader
ResourceManager::loadShaderFromFile(const char *vertexFile, const char *fragmentFile, const char *geometryFile) {
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vertexFile);
        std::ifstream fragmentShaderFile(fragmentFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (geometryFile != nullptr)
        {
            std::ifstream geometryShaderFile(geometryFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    Shader shader;
    shader.compile(vertexCode.c_str(), fragmentCode.c_str(), !geometryCode.empty() ? geometryCode.c_str() : nullptr);
    return shader;
}

Texture2d
ResourceManager::loadTextureFromFile(const char *file, bool alpha) {
    Texture2d texture;
    if (alpha) {
        texture.internal_format = GL_RGBA;
        texture.image_format = GL_RGBA;
    }
    int width, height, channels;
    unsigned char *data = stbi_load(file, &width, &height, &channels, 0);

    texture.generate(width, height, data);

    stbi_image_free(data);
    return texture;
}

Map 
ResourceManager::loadMapFromFile(const char *file) {
    std::ifstream mapFile(file);
    std::string line;
    std::vector<std::vector<int>> data;

    if (mapFile.is_open()) {
        while (std::getline(mapFile, line)) {
            std::stringstream ssline(line);
            std::string c;
            std::vector<int> row;
            while (std::getline(ssline, c, ' ')) {
                row.push_back(std::atoi(c.c_str()));
            }
            data.push_back(row);
        }
        mapFile.close();
    }

    return Map(data);
}
