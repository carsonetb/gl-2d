#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <unordered_map>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "color.hpp"

using namespace glm;

Color::Color(float re, float gr, float bl, float al) {
    r = re;
    g = gr;
    b = bl;
    a = al;
}

Color::Color(float re, float gr, float bl) {
    r = re;
    g = gr;
    b = bl;
    a = 1.0f;
}

Color::Color(glm::vec4 col) {
    r = col.r;
    g = col.g;
    b = col.b;
    a = col.a;
}

Color::Color(glm::vec3 col) {
    r = col.r;
    g = col.g;
    b = col.b;
    a = 1.0f;
}

glm::vec4 Color::to_vector() {
    return glm::vec4(r, g, b, a);
}