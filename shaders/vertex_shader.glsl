#version 330 core

uniform mat4 matrix;

layout(location = 0) in vec3 vertex_position;

out vec2 pos;

void main() {
    gl_Position = matrix * vec4(vertex_position, 1);
    pos = vertex_position.xy;
}