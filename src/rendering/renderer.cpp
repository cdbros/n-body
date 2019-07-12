#include "renderer.h"
#include "shaders.h"

#define GL_GLEXT_PROTOTYPES
#include <GL/glx.h>
#include <GL/gl.h>
#include <X11/X.h>
#include <X11/keysym.h>

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
  m_vao = std::make_unique<QOpenGLVertexArrayObject>(this);
  m_vao->create();
  //glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &VBO);
  m_vao->bind();
  //glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  //m_vao->unbind();
}

void Renderer::render() {
  if (!m_program) {
    init();
  }

  m_program->bind();

  glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
  clearColorViewPort(0.2f, 0.3f, 0.3f, 1.0f);

  m_vao->bind();
  glDrawArrays(GL_TRIANGLES, 0, 3);

  m_program->release();
  m_window->resetOpenGLState();
}
