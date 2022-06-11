#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_coord;
layout(location = 2) in vec3 a_normal;

uniform mat4 wvp;
uniform mat4 w;

out vec2 v_coord;
out vec3 v_pos;
out vec3 v_normal;

void main() {
    v_normal = normalize(w * vec4(a_normal, 0.0)).xyz;
    v_pos = (w * vec4(a_position, 0.0)).xyz;
    v_coord = a_coord;
    gl_Position = wvp * vec4(a_position, 1.0);
}
