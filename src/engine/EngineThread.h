#pragma once

#include "Engine.h"
#include <QThread>

class EngineThread : public QThread {
    Q_OBJECT

  private:
    void run() override;

  public:
    explicit EngineThread(unsigned tickStep = 70);

    inline void stopEngine() { m_shouldRun = false; }

  signals:
    void updateParams(RendererInterface params);
    void renderReady();

  private:
    Engine m_engine;
    unsigned m_tickStep;
    bool m_shouldRun;
    bool m_rateLimit;
};
