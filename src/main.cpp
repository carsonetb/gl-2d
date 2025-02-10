#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "public/window.hpp"
#include "drawing/drawer.hpp"
#include "drawing/text.hpp"

using namespace glm;

Window window = Window(1024, 1000, (char*)"Title", 4);

int main() {
    TextRenderer renderer;

    do {
        window.fill(glm::vec4(0.0, 0.0, 0.2, 1.0));

        // drawer.rectangle(window, glm::vec2(-0.5, -0.5), glm::vec2(1, 1), 5, 0.1f);
        // drawer.line(window, glm::vec2(-0.5, -0.5), glm::vec2(0.5, 0.5), 0.1f);
        // drawer.circle(window, glm::vec2(0, 0), 0.5, 0.05);
        renderer.render_text("Hi!", 20.0f, 20.0f, 1.0f, glm::vec3(1));

        window.update();
    }
    while (!window.is_key_pressed(GLFW_KEY_ESCAPE) && !window.should_close());

    window.close();

    return 0;

}