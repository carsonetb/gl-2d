#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "../drawing/drawer.hpp"
// Dumb because we already included it in this long chain ):
// #include "../resc/helpers.hpp"
#include "../public/window.hpp"

// Calculates the matrix.
glm::mat4 calculate_matrix(Window window) {
    glm::vec2 window_size = window.get_size();
    return glm::scale(glm::mat4(1), glm::vec3(window_size.y / window_size.x, 1.0, 1.0));
}

// Creates a Drawer.
Drawer::Drawer() {
    glGenVertexArrays(1, &vertex_id);
    glBindVertexArray(vertex_id);

    // Wow, very good for performance to load these shaders for every drawer!!!!
    default_program_id = load_shaders("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    circle_program_id = load_shaders("shaders/vertex_shader.glsl", "shaders/circle/fragment_shader.glsl");
    rect_program_id = load_shaders("shaders/vertex_shader.glsl", "shaders/rect/fragment_shader.glsl");

    uniform_hashmap["default:matrix"] = glGetUniformLocation(default_program_id, "matrix");
    uniform_hashmap["circle:center"] = glGetUniformLocation(circle_program_id, "center");
    uniform_hashmap["circle:radius"] = glGetUniformLocation(circle_program_id, "radius");
    uniform_hashmap["circle:width"] = glGetUniformLocation(circle_program_id, "width");
    uniform_hashmap["circle:matrix"] = glGetUniformLocation(circle_program_id, "matrix");
    uniform_hashmap["rect:bottom_left"] = glGetUniformLocation(rect_program_id, "bl");
    uniform_hashmap["rect:dimensions"] = glGetUniformLocation(rect_program_id, "wh");
    uniform_hashmap["rect:border_radius"] = glGetUniformLocation(rect_program_id, "border_radius");
    uniform_hashmap["rect:matrix"] = glGetUniformLocation(rect_program_id, "matrix");
    uniform_hashmap["rect:width"] = glGetUniformLocation(rect_program_id, "width");

    glGenBuffers(1, &vertex_buffer);
}

// Updates the vertex buffer.
void Drawer::update_vertex_buffer(GLsizeiptr size, GLfloat buffer[], int vertices) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
    num_vertices = vertices;
}

// Draws a triangle.
void Drawer::triangle(Window window, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3) {
    GLfloat buffer_data[] = {
        p1.x, p1.y, 0.0f,
        p2.x, p2.y, 0.0f,
        p3.x, p3.y, 0.0f,
    };
    update_vertex_buffer(sizeof(buffer_data), buffer_data, 3);
    glUseProgram(default_program_id);
    glUniformMatrix4fv(uniform_hashmap["default:matrix"], 1, GL_FALSE, &calculate_matrix(window)[0][0]);
    update();
}

void Drawer::rectangle(Window window, glm::vec2 pos, glm::vec2 wh, float width, float border_radius) {
    GLfloat buffer_data[] = {
        pos.x       , pos.y,        0.0f,
        pos.x + wh.x, pos.y,        0.0f,
        pos.x       , pos.y + wh.y, 0.0f,
        pos.x + wh.x, pos.y,        0.0f,
        pos.x       , pos.y + wh.y, 0.0f,
        pos.x + wh.x, pos.y + wh.y, 0.0f,
    };
    update_vertex_buffer(sizeof(buffer_data), buffer_data, 6);
    glUseProgram(rect_program_id);
    glUniformMatrix4fv(uniform_hashmap["rect:matrix"], 1, GL_FALSE, &calculate_matrix(window)[0][0]);
    glUniform2f(uniform_hashmap["rect:bottom_left"], pos.x, pos.y);
    glUniform2f(uniform_hashmap["rect:dimensions"], wh.x, wh.y);
    glUniform1f(uniform_hashmap["rect:border_radius"], border_radius);
    glUniform1f(uniform_hashmap["rect:width"], width / window.get_size().x);
    update();
}

void Drawer::rectangle(Window window, float width, glm::vec2 pos, glm::vec2 wh) {
    rectangle(window, pos, wh, width, -1.0f);
}

// Draws a material 5 rectangle.
void Drawer::rectangle(Window window, glm::vec2 pos, glm::vec2 wh, float border_radius) {
    rectangle(window, pos, wh, -1.0, border_radius);
}

// Draws a rectangle.
void Drawer::rectangle(Window window, glm::vec2 pos, glm::vec2 wh) {
    rectangle(window, pos, wh, -1.0f);
}

// Rectangle=line
void Drawer::line(Window window, glm::vec2 p1, glm::vec2 p2, float width) {
    float divisor = window.get_size().y * (width / 2.0f);
    glm::vec2 rect1 = p1 + glm::rotate(glm::normalize(p2 - p1), 90.0f) / divisor; // top left
    glm::vec2 rect2 = p1 + glm::rotate(glm::normalize(p2 - p1), -90.0f) / divisor; // bottom left
    glm::vec2 rect3 = p2 + glm::rotate(glm::normalize(p1 - p2), -90.0f) / divisor; // top right
    glm::vec2 rect4 = p2 + glm::rotate(glm::normalize(p1 - p2), 90.0f) / divisor; // bottom right
    GLfloat buffer_data[] = {
        rect1.x, rect1.y, 0.0f,
        rect3.x, rect3.y, 0.0f,
        rect2.x, rect2.y, 0.0f,
        rect4.x, rect4.y, 0.0f,
        rect3.x, rect3.y, 0.0f,
        rect2.x, rect2.y, 0.0f,
    };
    update_vertex_buffer(sizeof(buffer_data), buffer_data, 6);
    glUseProgram(default_program_id);
    glUniformMatrix4fv(uniform_hashmap["default:matrix"], 1, GL_FALSE, &calculate_matrix(window)[0][0]);
    update();
}

// Draws a line.
void Drawer::line(Window window, glm::vec2 p1, glm::vec2 p2) {
    line(window, p1, p2, 1.0f);
}

void Drawer::circle(Window window, glm::vec2 pos, float radius, float width) {
    GLfloat buffer_data[] = {
        pos.x - radius, pos.y - radius, 0.0f,
        pos.x + radius, pos.y - radius, 0.0f,
        pos.x - radius, pos.y + radius, 0.0f,
        pos.x + radius, pos.y - radius, 0.0f,
        pos.x - radius, pos.y + radius, 0.0f,
        pos.x + radius, pos.y + radius, 0.0f,
    };
    update_vertex_buffer(sizeof(buffer_data), buffer_data, 6);
    glUseProgram(circle_program_id);
    glUniform2f(uniform_hashmap["circle:center"], pos.x, pos.y);
    glUniform1f(uniform_hashmap["circle:radius"], radius);
    glUniform1f(uniform_hashmap["circle:width"], width);
    glUniformMatrix4fv(uniform_hashmap["circle:matrix"], 1, GL_FALSE, &calculate_matrix(window)[0][0]);
    update();
}

// Draws a circle.
void Drawer::circle(Window window, glm::vec2 pos, float radius) {
    circle(window, pos, radius, -1.0f);
}

// Updates the drawer.
void Drawer::update() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
    glDisableVertexAttribArray(0);
}


GLuint Drawer::load_shaders(const char* vertex_filepath, const char* fragment_filepath) {
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertex_shader_code;
    std::ifstream vertex_shader_stream(vertex_filepath, std::ios::in);
    if (vertex_shader_stream.is_open()) {
        std::stringstream sstr;
        sstr << vertex_shader_stream.rdbuf();
        vertex_shader_code = sstr.str();
        vertex_shader_stream.close();
    }
    else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_filepath);
		getchar();
		return 0;
	}
    
    std::string fragment_shader_code;
	std::ifstream fragment_shader_stream(fragment_filepath, std::ios::in);
	if(fragment_shader_stream.is_open()){
		std::stringstream sstr;
		sstr << fragment_shader_stream.rdbuf();
		fragment_shader_code = sstr.str();
		fragment_shader_stream.close();
	}
    else {
		printf("Impossible to open %s. Are you in the right directory? Don't forget to read the FAQ !\n", fragment_filepath);
		getchar();
		return 0;
	}
    GLint result = GL_FALSE;
    int info_log_length;

	printf("Compiling shader : %s\n", vertex_filepath);
	char const * vertex_source_pointer = vertex_shader_code.c_str();
	glShaderSource(vertex_shader_id, 1, &vertex_source_pointer , NULL);
	glCompileShader(vertex_shader_id);

	// Check Vertex Shader
	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if ( info_log_length > 0 ){
		std::vector<char> vertex_shader_error(info_log_length+1);
		glGetShaderInfoLog(vertex_shader_id, info_log_length, NULL, &vertex_shader_error[0]);
		printf("%s\n", &vertex_shader_error[0]);
	}

    // Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_filepath);
	char const * FragmentSourcePointer = fragment_shader_code.c_str();
	glShaderSource(fragment_shader_id, 1, &FragmentSourcePointer , NULL);
	glCompileShader(fragment_shader_id);

	// Check Fragment Shader
	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
	if ( info_log_length > 0 ){
		std::vector<char> fragment_shader_error(info_log_length+1);
		glGetShaderInfoLog(fragment_shader_id, info_log_length, NULL, &fragment_shader_error[0]);
		printf("%s\n", &fragment_shader_error[0]);
	}

    printf("Linking program\n");
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0) {
        std::vector<char> program_error_message(info_log_length + 1);
        glGetProgramInfoLog(program_id, info_log_length, NULL, &program_error_message[0]);
        printf("%s\n", &program_error_message[0]);
    }

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}