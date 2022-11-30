#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec3 a_vertex_color;

uniform mat4 wvp;
uniform mat4 w;

out vec2 v_uv;
out vec3 v_normal;
out vec3 v_color;

void main() {
    v_uv = a_uv;
    v_normal = (w * vec4(a_normal, 0.0)).xyz;
    v_color = a_vertex_color;
    gl_Position = wvp * vec4(a_position, 1.0);
}
