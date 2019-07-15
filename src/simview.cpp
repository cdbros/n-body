#include "SimView.h"

SimView::SimView(QWidget *parent) :
    QOpenGLWidget(parent),
    m_renderer{std::make_unique<Renderer>(this)}
{
    QSizePolicy spSimView(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spSimView.setHorizontalStretch(2);
    spSimView.setVerticalStretch(2);

    setSizePolicy(spSimView);
    setObjectName(QString::fromUtf8("simView"));
}

SimView::~SimView() {
    m_engineThread.stopEngine();
    m_engineThread.quit();
    m_engineThread.wait();
}

void SimView::initializeGL() {
    m_renderer->initialize();
    connect(&m_engineThread, &EngineThread::renderReady, m_renderer.get(), &Renderer::renderReady);
    m_engineThread.start();
}

void SimView::paintGL() {
    m_renderer->render();
}

void SimView::resizeGL(int width, int height) {
    m_renderer->resize(width, height);
}
