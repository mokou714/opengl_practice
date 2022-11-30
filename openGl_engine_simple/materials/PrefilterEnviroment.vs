#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec3 a_normal;

out vec3 localPos;
out vec2 uv;

void main() {
    uv = a_uv;
    localPos = a_position;
    gl_Position = vec4(a_position, 1.0);
}
