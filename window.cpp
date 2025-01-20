#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "window.hpp"

using namespace glm;

Window::Window(const int window_width, const int window_height, char* window_title, const int window_antialias_level) {
    width = window_width;
    height = window_height;
    title = window_title;
    antialias_level = window_antialias_level;
    init();
    int x = 0;
    int y = 0;
    glfwGetWindowSize(window, &x, &y);
    size.x = x;
    size.y = y;
}

Window::Window(const int width, const int height, char* title) {
    Window(width, height, title, 4);
}

Window::Window(const int width, const int height) {
    Window(width, height, (char*)"Untitled window");
}

Window::Window() {
    Window(1024, 768);
}

void Window::fill(glm::vec4 color) {
    glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(color.x, color.y, color.z, color.w);
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::is_key_pressed(int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Window::should_close() {
    return glfwWindowShouldClose(window);
}

void Window::close() {
    glfwTerminate();
}

glm::vec2 Window::get_size() {
    return size;
}

int Window::init() {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW window.");
        getchar();
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, antialias_level);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make macOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        printf("Failed to open GLFW window.");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

    return 0;
}