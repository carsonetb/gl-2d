#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window {
    public:
        int antialias_level;
        int width;
        int height;
        char* title;

        Window(const int width, const int height, char* title, const int antialias_level);
        Window(const int width, const int height, char* title);
        Window(const int width, const int height);
        Window();
        void update();
        void fill(glm::vec4 color);
        bool is_key_pressed(int key);
        bool should_close();
        void close();
        glm::vec2 get_size();
        
    private:
        GLFWwindow* window;
        glm::vec2 size;

        int init();
};

#endif