#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_coords;
layout(location = 2) in vec3 a_normals;

uniform mat4 wvp;
uniform mat4 wv;

out vec2 v_coords;
out vec4 v_normals;

void main() {
    v_normals = wv * vec4(a_normals, 0.0);
    v_coords = a_coords;
    gl_Position = wvp * vec4(a_position, 1.0);
}
