#ifndef COLOR_H
#define COLOR_h

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <unordered_map>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

class Color {
    public:
        Color(float re, float gr, float bl, float al);
        Color(float re, float gr, float bl);
        Color(glm::vec4 col);
        Color(glm::vec3 col);
        float r;
        float g;
        float b;
        float a;
        
        glm::vec4 to_vector();
};

#endif