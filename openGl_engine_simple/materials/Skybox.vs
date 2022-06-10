#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 wvp;

out vec3 v_pos;

void main() {
    v_pos = a_position;
    gl_Position = wvp * vec4(a_position, 1.0);
}
