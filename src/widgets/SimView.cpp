#include "SimView.h"

Q_DECLARE_METATYPE(RendererInterface);

SimView::SimView(QWidget *parent) : QOpenGLWidget(parent), m_renderer{std::make_unique<Renderer>(this)} {
    QSizePolicy spSimView(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spSimView.setHorizontalStretch(3);

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
    qRegisterMetaType<RendererInterface>();
    connect(&m_engineThread, &EngineThread::updateParams, m_renderer.get(), &Renderer::updateParams);
    connect(&m_engineThread, &EngineThread::renderReady, m_renderer.get(), &Renderer::renderReady);
    m_engineThread.start();
}

void SimView::paintGL() { m_renderer->render(); }

void SimView::resizeGL(int width, int height) { m_renderer->resize(width, height); }
