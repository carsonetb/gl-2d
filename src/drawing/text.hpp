#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "glfreetype/glfreetypetext.hpp"
#include "shader.hpp"

struct Character {
    unsigned int texture_id;
    glm::ivec2   size;
    glm::ivec2   bearing;   
    unsigned int advance;    
};

class TextRenderer {
    public:
        TextRenderer(const char* font, const int size);
        TextRenderer(const char* font);
        TextRenderer(const int size);
        TextRenderer();

        void render_text(std::string text, float x, float y, float scale, glm::vec3 color);

    private:
        const glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 0.0f, 1000.0f);
        std::unordered_map<char, Character> characters;
        unsigned int VAO, VBO;
        Shader shader;
        glfreetype::font_data font;
};

#endif