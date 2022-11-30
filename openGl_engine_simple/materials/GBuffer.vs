#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec3 a_normal;

uniform mat4 wvp;
uniform mat4 w;

out vec4 v_pos;
out vec2 v_uv;
out vec4 v_normal;

void main() {
    v_pos = w * vec4(a_position, 1.0);
    v_uv = a_uv;
    v_normal = w * (vec4(a_normal, 0.0 ));
    gl_Position = wvp * vec4(a_position, 1.0);
}
