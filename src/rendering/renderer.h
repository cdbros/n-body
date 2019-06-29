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

private:
  QSize m_viewportSize{};
  std::unique_ptr<QOpenGLShaderProgram> m_program{};
  QQuickWindow *m_window;
};

#endif // RENDERER_H
