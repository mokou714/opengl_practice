#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec3 a_normal;
layout(location = 3) in vec3 a_normal2;

uniform mat4 wvp;
uniform mat4 w;
uniform mat4 v;
uniform mat4 p;
uniform float back_face_pass;
uniform float use_normal2;
uniform vec3 camera_pos;

out vec2 v_uv;
out vec3 v_pos;
out vec3 v_normal;
out vec3 v_normal2;

void main() {
    v_uv = a_uv;
    vec4 w_normal = w * vec4(a_normal, 0.0);
    vec4 w_normal2 = w * vec4(a_normal2, 0.0);
    v_normal = normalize(w_normal.xyz);
    v_normal2 = normalize(w_normal2.xyz);
    v_pos = (w * vec4(a_position, 1.0)).xyz;
    vec3 view_dir = normalize(camera_pos - v_pos);
    vec4 screen_pos;
    if(back_face_pass == 0.0)
    {
        screen_pos = wvp * vec4(a_position, 1.0);
    }
    else
    {   
        
        vec3 outline_normal;
        if(use_normal2 == 0.0)
        {
            outline_normal = v_normal * 0.3;
        }
        else{
            outline_normal = v_normal2 * 0.3;
        }
        //法线外扩
        mat4 v_offset_mat = mat4(1.0, 0.0, 0.0, 0.0,  // 1. column
                                 0.0, 1.0, 0.0, 0.0,  // 2. column
                                 0.0, 0.0, 1.0, 0.0,  // 3. column
                                 outline_normal.x, outline_normal.y, outline_normal.z, 1.0
                                );
        
        screen_pos = p * v * v_offset_mat * vec4(v_pos, 1.0);
    }
    gl_Position = screen_pos;
}
