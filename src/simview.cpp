#include "simview.h"

SimView::SimView(QWidget *parent) : QOpenGLWidget(parent) {}

void SimView::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(1.0, 0.0, 0.0, 1.0);
}

void SimView::paintGL() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void SimView::resizeGL(int width, int height) { QOpenGLWidget::resizeGL(width, height); }
