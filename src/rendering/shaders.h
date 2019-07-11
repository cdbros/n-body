#ifndef RENDERING_SHADERS_H
#define RENDERING_SHADERS_H

#include <QString>

const QString vertexShaderSource = R"glsl(
#version 410 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 offset;

uniform mat4 mvp;
out vec2 vpos;

void main() {
    vpos = pos;
    gl_Position = mvp * vec4(pos + offset, 0.0f, 1.0);
}
)glsl";

const QString fragmentShaderSource = R"glsl(
#version 410 core

out vec4 frag_color;
in vec2 vpos;

void main() {
    float dis = sqrt(dot(vpos, vpos));
    dis = 0.5f - dis;
    dis = max(dis, 0.0f);
    dis = ceil(dis / 0.5f);
    frag_color = vec4(1.0f, 1.0f, 1.0f, dis);
}
)glsl";

#endif // RENDERING_SHADERS_H
