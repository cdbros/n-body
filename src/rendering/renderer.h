#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QQuickWindow>

class Renderer : public QObject, protected QOpenGLFunctions {
  Q_OBJECT

public:
  void setViewportSize(const QSize &size) noexcept;
  void setWindow(QQuickWindow *window) noexcept;

public slots:
  void render();

private:
  void init();

  inline void clearColorViewPort(GLclampf red, GLclampf green, GLclampf blue,
                                 GLclampf alpha) {
    glScissor(0, 0, m_viewportSize.width(), m_viewportSize.height());
    glEnable(GL_SCISSOR_TEST);
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT);
  }

private:
  QSize m_viewportSize{};
  std::unique_ptr<QOpenGLShaderProgram> m_program{};
  QQuickWindow *m_window;
  uint32_t m_vao;
};

#endif // RENDERER_H
