
#include "renderer.h"

Renderer::Renderer() {
  m_program = nullptr;
  m_viewportSize = QSize(0, 0);
}

Renderer::~Renderer() {
  delete m_program;
}

void Renderer::setViewportSize(const QSize &size) {
  m_viewportSize = size;
}

void Renderer::setWindow(QQuickWindow *window) {
    m_window = window;
}

void Renderer::init() {
  initializeOpenGLFunctions();

  m_program = new QOpenGLShaderProgram();
  m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Vertex,
                                              "attribute highp vec4 vertices;"
                                              "varying highp vec2 coords;"
                                              "void main() {"
                                              "    gl_Position = vertices;"
                                              "    coords = vertices.xy;"
                                              "}");
  m_program->addCacheableShaderFromSourceCode(QOpenGLShader::Fragment,
                                              "uniform lowp float t;"
                                              "varying highp vec2 coords;"
                                              "void main() {"
                                              "    lowp float i = 1. - (pow(abs(coords.x), 4.) + pow(abs(coords.y), 4.));"
                                              "    i = smoothstep(t - 0.8, t + 0.8, i);"
                                              "    i = floor(i * 20.) / 20.;"
                                              "    gl_FragColor = vec4(coords * .5 + .5, i, i);"
                                              "}");

  m_program->link();
}

void Renderer::render() {
  if (!m_program) {
    init();
  }

  m_program->bind();

  glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());

  glBegin(GL_TRIANGLES);
  glVertex2f(-0.5f, -0.5f);
  glVertex2f(0.0f, 0.5f);
  glVertex2f(0.5f, -0.5f);
  glEnd();

  m_program->release();
  m_window->resetOpenGLState();
}


