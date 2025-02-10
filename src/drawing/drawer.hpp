#ifndef DRAWER_H
#define DRAWER_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <unordered_map>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "../public/window.hpp"

class Drawer {
    public:
        Drawer();
        void triangle(Window window, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3);
        void rectangle(Window window, glm::vec2 pos, glm::vec2 wh, float width, float border_radius);
        void rectangle(Window window, glm::vec2 pos, glm::vec2 wh, float border_radius);
        void rectangle(Window window, glm::vec2 pos, glm::vec2 dimensions);
        void rectangle(Window window, float width, glm::vec2 pos, glm::vec2 wh);
        void circle(Window window, glm::vec2 pos, float radius, float width);
        void circle(Window window, glm::vec2 pos, float radius);
        void line(Window window, glm::vec2 p1, glm::vec2 p2, float width);
        void line(Window window, glm::vec2 p1, glm::vec2 p2);

    private:
        enum DrawType: int {
            TRIANGLE,
            RECTANGLE,
            CIRCLE,
        };

        void update_vertex_buffer(GLsizeiptr size, GLfloat buffer[], int num_vertices);
        void update();
        GLuint load_shaders(const char* vertex_filepath, const char* fragment_filepath);

        int num_vertices;
        GLuint vertex_buffer;
        GLuint vertex_id;
        GLuint default_program_id;
        GLuint circle_program_id;
        GLuint rect_program_id;
        std::unordered_map<std::string, GLuint> uniform_hashmap;
};

#endif