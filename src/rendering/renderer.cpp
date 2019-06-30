
#include "renderer.h"
#include "shaders.h"

#include <memory>

void Renderer::setViewportSize(const QSize &size) noexcept {
  m_viewportSize = size;
}

void Renderer::setWindow(QQuickWindow *window) noexcept { m_window = window; }

void Renderer::init() {
  initializeOpenGLFunctions();

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
  if (!m_program) {
    init();
  }

  m_program->bind();

  glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
  clearColorViewPort(0.2f, 0.3f, 0.3f, 1.0f);

  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  m_program->release();
  m_window->resetOpenGLState();
}
