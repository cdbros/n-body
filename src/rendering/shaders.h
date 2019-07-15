#ifndef RENDERING_SHADERS_H
#define RENDERING_SHADERS_H

#include <QString>

const QString vertexShaderSource =
#include "shaders/vertex.glsl"
    ;

const QString fragmentShaderSource =
#include "shaders/fragment.glsl"
    ;

#endif // RENDERING_SHADERS_H
