R"glsl(

#version 410 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 offset;

uniform mat4 mvp;
out vec2 vpos;

void main() {
    vpos = pos;
    gl_Position = mvp * vec4(pos.x + offset.x, pos.y + offset.y, offset.z, 1.0);
}

)glsl"
