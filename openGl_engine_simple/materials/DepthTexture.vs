#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_uv;

uniform mat4 wvp;
uniform mat4 w;
uniform vec4 centers[9];
uniform vec3 model_center_pos;

out vec2 v_uv;
out vec3 v_vertex;
out vec3 v_model_center_pos;

void main() {
    v_model_center_pos = (w * vec4(model_center_pos, 0)).xyz;
    v_uv = a_uv;
    v_vertex = (w * vec4(a_position, 0.0)).xyz;
    gl_Position = wvp * vec4(a_position, 1.0);
}
