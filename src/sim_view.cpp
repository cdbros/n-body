#include "sim_view.h"

#include <QtQuick/qquickwindow.h>
#include <memory>

SimView::SimView() {
  connect(this, &QQuickItem::windowChanged, this,
          &SimView::handleWindowChanged);
}

void SimView::sync() {
  if (!m_renderer) {
    m_renderer = std::make_unique<Renderer>();
    connect(window(), &QQuickWindow::afterRendering, m_renderer.get(),
            &Renderer::render, Qt::DirectConnection);
  }
  updateViewportSize();
  m_renderer->setWindow(window());
}

void SimView::handleWindowChanged(QQuickWindow *window) const {
  if (window) {
    connect(window, &QQuickWindow::beforeSynchronizing, this, &SimView::sync,
            Qt::DirectConnection);

    // prevents QML from clearing
    window->setClearBeforeRendering(false);
  }
}
