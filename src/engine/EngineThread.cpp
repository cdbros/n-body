#include "EngineThread.h"

EngineThread::EngineThread() : m_engine{}, m_tickStep(10), m_shouldRun(true), m_rateLimit(false) {}

inline auto getTimeUsec() {
    using namespace std::chrono;
    return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

void EngineThread::run() {
    decltype(getTimeUsec()) lastRenderTime;
    emit updateParams(m_engine.getParams());
    while (m_shouldRun) {
        lastRenderTime = getTimeUsec();
        m_engine.step(m_tickStep);
        emit renderReady();
        auto delta = getTimeUsec() - lastRenderTime;
        if (m_rateLimit && delta < m_tickStep) {
            usleep(m_tickStep - delta);
        }
    }
}
