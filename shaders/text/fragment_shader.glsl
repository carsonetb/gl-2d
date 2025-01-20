#version 330 core

uniform sampler2D text;
uniform vec3 textColor;

in vec2 tex_coords;

out vec4 color;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, tex_coords).r);
    color = vec4(textColor, 1.0) * sampled;
} 