#ifndef SIMULATION_H
#define SIMULATION_H

#include <QtQuick/QQuickItem>
#include "src/rendering/renderer.h"

class SimView : public QQuickItem {
  Q_OBJECT

public:
  SimView();
  ~SimView();

public slots:
  void sync();
  void cleanup();

private slots:
  void handleWindowChanged(QQuickWindow *window);

private:
    Renderer *m_renderer;
};

#endif // SIMULATION_H
