#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QQuickWindow>

class Renderer : public QObject, protected QOpenGLFunctions {
Q_OBJECT

public:
  Renderer();
  ~Renderer() override;

  void setViewportSize(const QSize &size);
  void setWindow(QQuickWindow *window);

public slots:
  void render();

private:
  void init();

private:
  QSize m_viewportSize;
  QOpenGLShaderProgram *m_program;
  QQuickWindow *m_window;
};

#endif // RENDERER_H
