#pragma once

#include <QOpenGLFunctions>

struct RendererInterface {
    const GLfloat *objCoords;
    const GLfloat *objRadii;
    std::size_t numObjs;
};
