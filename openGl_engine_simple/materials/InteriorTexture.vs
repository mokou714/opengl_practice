#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 wvp;
uniform mat4 w;

out vec3 v_vertex;

void main() {
    v_vertex = (w * vec4(position, 0.0)).xyz;
    gl_Position = wvp * vec4(position, 1.0);
}
