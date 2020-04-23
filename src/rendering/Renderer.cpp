#include "Renderer.h"
#include "Error.h"
#include "Shaders.h"
#include <QVector3D>
#include <iostream>

Renderer::Renderer(QOpenGLWidget *openGLView) : m_openGLView{openGLView}, QObject(openGLView) {}

void Renderer::initialize() {
    initializeOpenGLFunctions();

    m_program = std::make_unique<QOpenGLShaderProgram>();

    // create shaders and link
    glCheck(m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource));
    glCheck(m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource));
    glCheck(m_program->link());

    GLfloat vertices[] = {
        -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f,
    };
    GLuint indices[] = {
        0, 1, 2, 2, 3, 0,
    };

    glCheck(glGenVertexArrays(1, &m_vao));
    glCheck(glGenBuffers(1, &m_vbo));
    glCheck(glGenBuffers(1, &m_eab));
    glCheck(glGenBuffers(1, &m_obo));
    glCheck(glGenBuffers(1, &m_rbo));

    glCheck(glBindVertexArray(m_vao));

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    auto pos_loc = glCheck(m_program->attributeLocation("pos"));
    glCheck(glVertexAttribPointer(pos_loc, 2, GL_FLOAT, GL_FALSE, 0, 0));
    glCheck(glEnableVertexAttribArray(pos_loc));

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_obo));
    auto offset_loc = glCheck(m_program->attributeLocation("offset"));
    glCheck(glEnableVertexAttribArray(offset_loc));
    glCheck(glVertexAttribPointer(offset_loc, 3, GL_FLOAT, GL_FALSE, 0, 0));
    glCheck(glVertexAttribDivisor(offset_loc, 1));

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_rbo));
    auto radius_loc = glCheck(m_program->attributeLocation("radius"));
    glCheck(glEnableVertexAttribArray(radius_loc));
    glCheck(glVertexAttribPointer(radius_loc, 1, GL_FLOAT, GL_FALSE, 0, 0));
    glCheck(glVertexAttribDivisor(radius_loc, 1));

    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eab));
    glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    m_mvp_loc = glCheck(m_program->uniformLocation("mvp"));
    m_mvp = std::make_unique<QMatrix4x4>();
    m_mvp->setToIdentity();
    m_mvp->scale(m_zoom);
    m_mvp->translate(m_camX, m_camY);

    glCheck(m_program->bind());
    glCheck(m_program->setUniformValue(m_mvp_loc, *m_mvp));
    glCheck(m_program->release());

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    glCheck(glBindVertexArray(0));
}

void Renderer::updateParams(RendererInterface params) {
    m_engineParams = params;
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_rbo));
    glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m_engineParams.numObjs, m_engineParams.objRadii,
                         GL_STATIC_DRAW));
}

void Renderer::renderReady() { m_openGLView->update(); }

void Renderer::render() {
    m_program->bind();

    glCheck(glClearColor(0, 0, 0, 1));
    glCheck(glClear(GL_COLOR_BUFFER_BIT));

    if (m_mvp_changed) {
        m_mvp->scale(m_zoom);
        m_mvp->translate(m_translation);

        glCheck(m_program->setUniformValue(m_mvp_loc, *m_mvp));
        m_mvp_changed = false;
        m_translation = translationDefault;
        m_zoom = zoomDefault;
    }

    glCheck(glEnable(GL_BLEND));
    glCheck(glEnable(GL_DEPTH_TEST));
    glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    glCheck(glBindVertexArray(m_vao));

    // Coordinates updates on each render
    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_obo));
    glCheck(glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat) * m_engineParams.numObjs, m_engineParams.objCoords,
                         GL_DYNAMIC_DRAW));

    glCheck(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eab));
    glCheck(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, m_engineParams.numObjs));

    m_program->release();
}

void Renderer::wheelEvent(QWheelEvent *event) {
    auto numDegrees = event->angleDelta() / 8;
    auto numSteps = numDegrees.y();

    if (numSteps != 0) {
        m_zoom = zoomDefault + numSteps * zoomScale;
        m_mvp_changed = true;
    }
}

void Renderer::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        auto diff = QVector3D(event->localPos()) - m_mousePos;
        m_translation = diff * movScale;
        m_mvp_changed = true;
        m_mousePos = event->localPos();
    }
}

void Renderer::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        m_mousePos = QVector3D(event->localPos());
    }
}
