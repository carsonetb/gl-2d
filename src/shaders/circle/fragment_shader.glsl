#version 330 core

uniform vec2 center;
uniform float radius;
uniform float width;

in vec2 pos;

out vec3 color;

void main()
{
    if (width > 0 && pow(pos.x - center.x, 2) + pow(pos.y - center.y, 2) < pow(radius - width, 2)) {
        discard;
    }
    if (pow(pos.x - center.x, 2) + pow(pos.y - center.y, 2) > pow(radius, 2)) {
        discard;
    }
    color = vec3(1, 1, 1);
}