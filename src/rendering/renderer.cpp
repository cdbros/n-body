#include "renderer.h"
#include "shaders.h"

Renderer::Renderer(QOpenGLWidget *openGLView) : m_openGL_view{openGLView}, QObject(openGLView) {}

void Renderer::initialize() {
    initializeOpenGLFunctions();

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    m_program = std::make_unique<QOpenGLShaderProgram>();

    // create shaders and link
    m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,
                                                vertexShaderSource);
    m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
                                                fragmentShaderSource);
    m_program->link();

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f,  -0.5f, 0.0f, // right
        0.0f,  0.5f,  0.0f  // top
    };

    uint32_t VBO;
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &VBO);
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::render() {

    m_program->bind();

    glViewport(0, 0, m_openGL_view->width(), m_openGL_view->height());
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_program->release();
}

void Renderer::resize(int width, int height) {}
