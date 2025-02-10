#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <GL/glew.h>
#include <unordered_map>
#include <string>

#include "../drawing/shader.hpp"

class ShaderManager {
    public:
        ShaderManager();

        // Loads a shader. If this is called again with the same folder_path, it will return
        // the shader that has been cached.
        Shader load_shader(std::string folder_path);

        // Loads a shader. If this is called again with the same vertex_path and the same 
        // fragment path, it will return the shader that has been cached.
        Shader load_shader(std::string vertex_path, std::string fragment_path);

    private:
        std::unordered_map<std::string, Shader> temp_cache_folder;
        std::unordered_map<std::string, Shader> temp_cache_vertex;
};

#endif