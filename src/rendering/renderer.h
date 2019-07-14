#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

class Renderer : public QObject, protected QOpenGLFunctions {
  public:
    explicit Renderer(QOpenGLWidget *openGLView);

    void initialize();
    void render();
    void resize(int width, int height);

  private:
    QOpenGLWidget *m_openGL_view;
    std::unique_ptr<QOpenGLShaderProgram> m_program{};
    uint32_t m_vao;
};

#endif // RENDERER_H
