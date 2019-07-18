#include "Engine.h"
#include <cmath>
#include <limits>

static constexpr long double G = 6.673e-11;
static constexpr long double solarmass = 1.98892e30;
static constexpr long double distance_scale = 2e-8;
static constexpr long double time_scale = 1.0;

Body::Body(const Params &params)
    : rx(params.x0), ry(params.y0), vx(params.vx0), vy(params.vy0), ax(0), ay(0), fx(0), fy(0), mass(params.mass) {}

void Body::step(long double dt) {
    // Do calculations in higher precision
    ax = fx / mass;
    ay = fy / mass;

    // 4th order Runge-Kutta for (d/dt)^2 r = F/m
    long double halfdt = 0.5 * dt;
    long double dtax = dt * ax;
    long double dtay = dt * ay;
    rx += dt * vx + halfdt * dtax;
    ry += dt * vy + halfdt * dtay;
    vx += dtax;
    vy += dtay;

    // Write to coordinate array
    *px = static_cast<GLfloat>(distance_scale * rx);
    *py = static_cast<GLfloat>(distance_scale * ry);
}

void Body::resetForce() {
    fx = 0;
    fy = 0;
}

void Body::addGravity(Body &b) {
    long double dx = b.rx - rx;
    long double dy = b.ry - ry;
    long double distSq = dx * dx + dy * dy;
    long double fg = G * mass * b.mass / distSq;
    long double dist = sqrt(distSq);
    long double fgx = fg * dx / dist;
    long double fgy = fg * dy / dist;
    fx += fgx;
    fy += fgy;
    b.fx -= fgx;
    b.fy -= fgy;
}

Engine::Engine() : m_objs{}, m_objCoords{}, m_zIndex(0.0f) {
    constexpr std::size_t approxObjCount = 16384;
    m_objs.reserve(approxObjCount);
    m_objCoords.reserve(approxObjCount * 3); // (x, y, z) per object

    Body::Params p0(0, 0, 0, 0, 5.972e+29);
    Body::Params p1(0, 9000e+3, 2500e+3, 0, 200e+3);
    Body::Params p2(10000e+3, 0, 0, -2000e+3, 200e+3);
    Body::Params p3(20000e+3, 0, 1000e+3, 1000e+3, 200e+3);
    addObject(p0);
    addObject(p1);
    addObject(p2);
    addObject(p3);
}

void Engine::addObject(const Body::Params &params) {
    constexpr GLfloat zStep = 0.00001f;

    // Initialize object velocity and mass
    Body obj{params};
    auto &newObj = m_objs.emplace_back(obj);
    // Track coordinate vector before/after capacity
    auto prevCapacity = m_objCoords.capacity();
    auto newCoords = m_objCoords.insert(std::end(m_objCoords), 3, static_cast<GLfloat>(m_zIndex -= zStep));
    auto nextCapacity = m_objCoords.capacity();
    if (prevCapacity != nextCapacity) {
        // Vector has resized and iterators invalidated
        auto coordIt = std::begin(m_objCoords);
        for (auto objIt = std::begin(m_objs); objIt != std::end(m_objs); ++objIt, ++coordIt) {
            objIt->px = coordIt++;
            objIt->py = coordIt++;
        }
    } else {
        newObj.px = newCoords++;
        newObj.py = newCoords++;
    }
}

void Engine::step(unsigned tickStep) {
    long double dt = tickStep / 1000000.0f * time_scale;
    for (auto &obj : m_objs) {
        obj.resetForce();
    }
    for (auto flIt = std::begin(m_objs); flIt != std::end(m_objs); ++flIt) {
        for (auto slIt = std::next(flIt); slIt != std::end(m_objs); ++slIt) {
            flIt->addGravity(*slIt);
        }
    }
    for (auto &obj : m_objs) {
        obj.step(dt);
    }
}

const GLfloat *Engine::getObjCoords() const { return m_objCoords.data(); }

std::size_t Engine::getNumObjs() const { return m_objs.size(); }

EngineThread::EngineThread(unsigned tickStep)
    : m_engine{}, m_tickStep(tickStep), m_shouldRun(true), m_rateLimit(false) {}

inline auto getTimeUsec() {
    using namespace std::chrono;
    return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}

void EngineThread::run() {
    decltype(getTimeUsec()) lastRenderTime;
    while (m_shouldRun) {
        lastRenderTime = getTimeUsec();
        m_engine.step(m_tickStep);
        emit renderReady(m_engine.getObjCoords(), m_engine.getNumObjs());
        auto delta = getTimeUsec() - lastRenderTime;
        if (m_rateLimit && delta < m_tickStep) {
            usleep(m_tickStep - delta);
        }
    }
}
