#include "simulation_view.h"

#include <QtQuick/qquickwindow.h>

SimView::SimView() :
    m_renderer(nullptr) {

  connect(this, &QQuickItem::windowChanged, this, &SimView::handleWindowChanged);
}

SimView::~SimView() {
  delete m_renderer;
}

void SimView::sync() {
  if (!m_renderer) {
    m_renderer = new Renderer{};
    connect(window(), &QQuickWindow::afterRendering, m_renderer, &Renderer::render, Qt::DirectConnection);
  }
  m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
  m_renderer->setWindow(window());
}

void SimView::cleanup() {
  if (m_renderer) {
    delete m_renderer;
    m_renderer = nullptr;
  }
}

void SimView::handleWindowChanged(QQuickWindow *window) {
  if (window) {
    connect(window, &QQuickWindow::beforeSynchronizing, this, &SimView::sync, Qt::DirectConnection);
    connect(window, &QQuickWindow::sceneGraphInvalidated, this, &SimView::cleanup, Qt::DirectConnection);

    // If we allow QML to do the clearing, they would clear what we paint
    // and nothing would show.
    window->setClearBeforeRendering(false);
  }
}
