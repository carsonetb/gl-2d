#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <iostream>
#include <unordered_map>
#include "freetype/include/ft2build.h"
#include "freetype/freetype.h"

#include "window.hpp"
#include "drawer.hpp"

using namespace glm;

Window window = Window(1024, 1000, (char*)"Title", 4);

struct Character {
    unsigned int texture_id;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

std::unordered_map<char, Character> characters;

int main() {
    Drawer drawer;

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR: Freetype could not init FreeType Library" << "\n";
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "resources/arial.ttf", 0, &face)) {
        std::cout << "ERROR: Freetype failed to load font." << "\n";
        return -1;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        std::cout << "ERROR: Freetype failed to load Glyph" << "\n";  
        return -1;
    }

    for (unsigned char c = 0; c< 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR: Freetype failed to load Glyph" << "\n";
            continue;
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters[c] = character;
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glm::mat4 projection = glm::ortho(0.0f, window.get_size().x, 0.0f, window.get_size().y);
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    do {
        window.fill(glm::vec4(0.0, 0.0, 0.2, 1.0));

        // drawer.rectangle(window, glm::vec2(-0.5, -0.5), glm::vec2(1, 1), 5, 0.1f);
        // drawer.line(window, glm::vec2(-0.5, -0.5), glm::vec2(0.5, 0.5), 0.1f);
        drawer.circle(window, glm::vec2(0, 0), 0.5, 0.05);

        window.update();
    }
    while (!window.is_key_pressed(GLFW_KEY_ESCAPE) && !window.should_close());

    window.close();

    return 0;

}