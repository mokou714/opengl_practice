#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_coords;
layout(location = 2) in vec3 a_normals;

uniform mat4 world_view_projection;
uniform mat4 world_view;

out vec2 v_coords;
out vec4 v_normals;

void main() {
    v_normals = world_view * vec4(a_normals, 0.0);
    v_coords = a_coords;
    gl_Position = world_view_projection * vec4(a_position, 1.0);
}
