R"glsl(

#version 410 core

in vec2 pos;
in vec3 offset;
in float radius;

uniform mat4 mvp;

out vec2 vpos;
out float vradius;

void main() {
    vpos = radius * pos;
    vradius = radius;
    gl_Position = mvp * vec4(vpos.x + offset.x, vpos.y + offset.y, offset.z, 1.0);
}

)glsl"
