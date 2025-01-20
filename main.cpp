#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <glm/glm.hpp>
#include <iostream>

#include "window.hpp"
#include "drawer.hpp"

using namespace glm;

Window window = Window(1024, 1000, (char*)"Title", 4);

int main() {
    Drawer drawer;

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