#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <string>
#include <unordered_map>
#include <ft2build.h>
#include <freetype/freetype.h>

#include "glfreetype/glfreetypetext.hpp"
#include "text.hpp"
#include "shader.hpp"

using namespace std;

std::unordered_map<char, Character> characters;
const glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
unsigned int VAO, VBO;

TextRenderer::TextRenderer(const char* filepath, const int height) {
    glfreetype::font_data font;
    font.init(filepath, height);
}

TextRenderer::TextRenderer(const char* filepath) {
    TextRenderer(filepath, 25);
}

TextRenderer::TextRenderer(const int height) {
    TextRenderer((const char*)"../assets/arial.ttf", height);
}

TextRenderer::TextRenderer() {
    TextRenderer((const char*)"../assets/arial.ttf", 25);
}

void TextRenderer::render_text(std::string text, float x, float y, float scale, glm::vec3 color) {
    glPushMatrix();
    glLoadIdentity();
    glColor3ub(0,0,0xff);
    glfreetype::print(font, x, y, text);
    glPopMatrix();
}