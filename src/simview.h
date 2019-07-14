#ifndef SIMVIEW_H
#define SIMVIEW_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

class SimView : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

  public:
    explicit SimView(QWidget *parent = nullptr);

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
};

#endif // SIMVIEW_H
