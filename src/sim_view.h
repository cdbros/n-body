#ifndef SIMULATION_H
#define SIMULATION_H

#include <QtQuick/QQuickItem>
#include "src/rendering/renderer.h"

class SimView : public QQuickItem {
  Q_OBJECT

  Q_PROPERTY(int width WRITE setWidth)
  Q_PROPERTY(int height WRITE setHeight)

public:
  SimView();
  ~SimView();

public slots:
  void sync();
  void cleanup();

private slots:
  void handleWindowChanged(QQuickWindow *window);

private:
 void setWidth(int width);
 void setHeight(int height);
 void updateViewportSize();

private:
  int m_width;
  int m_height;
  Renderer *m_renderer;
};

#endif // SIMULATION_H
