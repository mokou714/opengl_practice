#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

uniform mat4 wvp;
uniform mat4 w;

uniform vec3 cam_pos;
uniform vec3 light_dir;

out vec3 v_vertex;
out vec2 v_uv;
out vec3 v_tbn_view_dir;
out vec3 v_tbn_light_dir;

void main() {
    v_uv = uv;
    v_vertex = (w*vec4(position, 0)).xyz;

    //默认用平面mesh TBN和世界坐标系对齐
    vec3 obj_normal = vec3(0.0, 1.0, 0.0);
    vec3 obj_tangent = vec3(1.0, 0.0, 0.0);
    vec3 obj_binormal = vec3(0.0, 0.0, 1.0);

    vec3 view_dir = -normalize(v_vertex-cam_pos);
    v_tbn_view_dir.x = dot(obj_tangent, view_dir);    
    v_tbn_view_dir.y = dot(obj_binormal, view_dir);    
    v_tbn_view_dir.z = dot(obj_normal, view_dir);

    v_tbn_light_dir.x = dot(obj_tangent, -light_dir);    
    v_tbn_light_dir.y = dot(obj_binormal, -light_dir);    
    v_tbn_light_dir.z = dot(obj_normal, -light_dir);
    
    gl_Position = wvp * vec4(position, 1.0);
}
