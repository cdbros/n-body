#ifndef SIMULATION_H
#define SIMULATION_H

#include "src/rendering/renderer.h"
#include <QtQuick/QQuickItem>

class SimView : public QQuickItem {
  Q_OBJECT

  Q_PROPERTY(int width READ getWidth WRITE setWidth)
  Q_PROPERTY(int height READ getHeight WRITE setHeight)

public:
  SimView();

public slots:
  void sync();
  void cleanup();

private slots:
  void handleWindowChanged(QQuickWindow *window) const;

private:
  inline void setWidth(int width) noexcept {
    m_width = width;
    updateViewportSize();
  }

  inline void setHeight(int height) noexcept {
    m_height = height;
    updateViewportSize();
  }

  inline void updateViewportSize() const noexcept {
    if (m_renderer) {
      m_renderer->setViewportSize(QSize(m_width, m_height) *
                                  window()->devicePixelRatio());
    }
  }

  [[nodiscard]] inline int getWidth() const noexcept { return m_width; }
  [[nodiscard]] inline int getHeight() const noexcept { return m_height; }

private:
  int m_width{};
  int m_height{};
  std::unique_ptr<Renderer> m_renderer{};
};

#endif // SIMULATION_H
