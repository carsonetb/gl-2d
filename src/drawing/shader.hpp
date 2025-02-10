#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

class Shader {
    public:
        Shader(std::string folder_path);
        Shader(std::string vertex, std::string fragment);
        Shader();

        void set_uniform(std::string uniform_name, int val);
        void set_uniform(std::string uniform_name, float val);
        void set_uniform(std::string uniform_name, glm::vec2 val);
        void set_uniform(std::string uniform_name, glm::vec3 val);
        void set_uniform(std::string uniform_name, glm::vec4 val);
        void set_uniform(std::string uniform_name, glm::mat4 val);
        void load_uniform(std::string uniform_name);

        GLuint shader_id;
    
    private:
        std::unordered_map<std::string, GLuint> uniform_map;
};

#endif