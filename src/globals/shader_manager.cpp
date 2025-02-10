#include <GL/glew.h>
#include <unordered_map>
#include <string>

#include "shader_manager.hpp"
#include "../drawing/shader.hpp"

Shader ShaderManager::load_shader(std::string folder_path) {
    if (temp_cache_folder.find(folder_path) == temp_cache_folder.end() && 
        temp_cache_vertex.find(folder_path + "/vertex_shader.glsl") == temp_cache_folder.end()) 
    {
        Shader loaded(folder_path);
        temp_cache_folder[folder_path] = loaded;
        return loaded;
    }
    return temp_cache_folder[folder_path];
}

Shader ShaderManager::load_shader(std::string vertex_path, std::string fragment_path) {
    if (temp_cache_vertex.find(vertex_path) == temp_cache_vertex.end()) {
        Shader loaded(vertex_path, fragment_path);
        temp_cache_vertex[vertex_path] = loaded;
        return loaded;
    }
    return temp_cache_vertex[vertex_path];
}