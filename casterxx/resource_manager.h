#ifndef __RESOURCE_MANAGER_H
#define __RESOURCE_MANAGER_H

#include <map>
#include <string>

#include "texture2d.h"
#include "shader.h"
#include "map.h"

class ResourceManager {
public:
    static Shader LoadShader(const char *vertexFile, const char *fragmentFile, const char *geometryFile, const char *name);
    static Texture2d LoadTexture(const char *file, bool alpha, const char *name);
    static Map LoadMap(const char *file, const char *name); 

    static Shader GetShader(const char *name);
    static Texture2d GetTexture(const char *name);
    static Map GetMap(const char *name);

private:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2d> textures;
    static std::map<std::string, Map> maps;

    ResourceManager() {}
    
    static Shader loadShaderFromFile(const char *vertexFile, const char *fragmentFile, const char *geometryFile = nullptr);

    static Texture2d loadTextureFromFile(const char *file, bool alpha);

    static Map loadMapFromFile(const char *file);
};

#endif /* __RESOURCE_MANAGER_H */
