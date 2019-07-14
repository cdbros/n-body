#ifndef SIMVIEW_H
#define SIMVIEW_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <memory>
#include <src/rendering/renderer.h>

class SimView : public QOpenGLWidget {
    Q_OBJECT

  public:
    explicit SimView(QWidget *parent = nullptr);

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

  private:
    std::unique_ptr<Renderer> m_renderer;
};

#endif // SIMVIEW_H
