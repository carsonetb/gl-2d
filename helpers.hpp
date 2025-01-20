#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>

#include "helpers.cpp"

GLuint load_shaders(const char* vertex_filepath, const char* fragment_filepath);
glm::vec2 screen_to_gl(Window window, glm::vec2 in);