#include <GL/glew.h>
#include <unordered_map>
#include <stdlib.h>
#include <string>
#include <glm/glm.hpp>

#include "shader.hpp"
#include "../resc/helpers.hpp"

using namespace std;
using namespace glm;

#define CHECK_NAME_VALID(uniform_name) \
    if (uniform_map.find(uniform_name) == uniform_map.end()) { \
        cout << "WARNING: Tried to set a uniform but that uniform had not been loaded.\n"; \
        load_uniform(uniform_name); \
    } \


using namespace std;

Shader::Shader(std::string folder_path) {
    shader_id = load_shaders((folder_path + "/vertex_shader.glsl").c_str(), (folder_path + "/fragment_shader.glsl").c_str());
}

Shader::Shader(std::string vertex, std::string fragment) {
    shader_id = load_shaders(vertex.c_str(), fragment.c_str());
}

Shader::Shader() {}

void Shader::load_uniform(std::string uniform_name) {
    uniform_map[uniform_name] = glGetUniformLocation(shader_id, uniform_name.c_str());
}

void Shader::set_uniform(std::string uniform_name, int val) {
    CHECK_NAME_VALID(uniform_name);
    glUniform1i(uniform_map[uniform_name], val);
}

void Shader::set_uniform(std::string uniform_name, float val) {
    CHECK_NAME_VALID(uniform_name);
    glUniform1f(uniform_map[uniform_name], val);
}

void Shader::set_uniform(std::string uniform_name, glm::vec2 val) {
    CHECK_NAME_VALID(uniform_name);
    glUniform2f(uniform_map[uniform_name], val.x, val.y);
}

void Shader::set_uniform(std::string uniform_name, glm::vec3 val) {
    CHECK_NAME_VALID(uniform_name);
    glUniform3f(uniform_map[uniform_name], val.x, val.y, val.z);
}

void Shader::set_uniform(std::string uniform_name, glm::mat4 val) {
    CHECK_NAME_VALID(uniform_name);
    glUniformMatrix4fv(uniform_map[uniform_name], 1, GL_FALSE, &val[0][0]);
}