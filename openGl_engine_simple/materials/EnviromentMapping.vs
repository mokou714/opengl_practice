#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 2) in vec3 a_normal;

uniform mat4 wvp;
uniform mat4 w;

out vec4 v_normal;
out vec4 v_pos;

void main() {
    v_normal = w * vec4(a_normal, 0.0);
    v_pos = w * vec4(a_position, 0.0);
    gl_Position = wvp * vec4(a_position, 1.0);
}
