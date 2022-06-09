#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_coords;

uniform mat4 world_view_projection;
uniform mat4 world_view;

out vec2 v_coords;
out vec3 v_pos;

void main() {
    v_coords = a_coords;
    v_pos = a_position;
    gl_Position = world_view_projection * vec4(a_position, 1.0);
}
