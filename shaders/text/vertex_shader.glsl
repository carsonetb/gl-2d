#version 330 core

uniform mat4 matrix;

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>

out vec2 tex_coords;

void main() {
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    tex_coords = vertex.zw;
}  