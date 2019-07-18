#include "Engine.h"
#include "Config.h"
<<<<<<< HEAD
#include <cmath>
=======
#include <algorithm>
#include <functional>
>>>>>>> upstream/master

Engine::Engine() : m_objs{}, m_objCoords{}, m_objRadii{}, m_zIndex(0.0f) {
    constexpr std::size_t approxObjCount = 16384;
    m_objs.reserve(approxObjCount);
    m_objCoords.reserve(approxObjCount * 3); // (x, y, z) per object
    m_objRadii.reserve(approxObjCount);

    Body::Params p0(-3000e+3, 0, 0, 2000e+3, 5.972e+29, 1000e+3);
    Body::Params p4(3000e+3, 0, 0, -2000e+3, 6.000e+29, 1000e+3);

    Body::Params p3(0, -38e+6, -12e+5, 0, 500e+3, 500e+3);
    Body::Params p2(40e+6, 0, 100e+3, -11e+5, 200e+3, 500e+3);
    Body::Params p1(0, 37e+6, 12e+5, 0, 300e+3, 500e+3);

    addObject(p0);
    addObject(p1);
    addObject(p2);
    addObject(p3);
    addObject(p4);
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

    // Track other parameters
    m_objRadii.push_back(static_cast<GLfloat>(Config::DISTANCE_SCALE * obj.radius));

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

inline auto getTimeUsec() {
    using namespace std::chrono;
    return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
}


#include <iostream>
#include <cstdlib>

void Engine::takeMetrics() {
    static std::size_t magCount = 0;
    static double start = getTimeUsec();
    ++magCount;

    if (m_lastTime == 0.0) {
        m_lastTime = getTimeUsec();
        m_frameCount = 0;
    }
    ++m_frameCount;
    if (m_frameCount == 60000) {
        long double framesPerSec = m_frameCount * 1e+6 / (getTimeUsec() - m_lastTime);
        m_lastTime = getTimeUsec();
        std::cout << "FPS: " << framesPerSec << std::endl;
        m_frameCount = 0;
    }
    if (magCount == 60000*100) {
        std::cout << "MAG_COUNT: " << std::endl;
        auto &o = m_objs[3];
        std::cout << (getTimeUsec() - start) / 1e+6 << std::endl;
        std::cout << o.rx << std::endl;
        std::cout << o.ry << std::endl;
        std::cout << o.vx << std::endl;
        std::cout << o.vy << std::endl;
        exit(0);
    }
}

void Engine::step(unsigned tickStep) {
    constexpr long double usec_to_sec = 1.0e+6;
    long double h = tickStep / usec_to_sec * Config::TIME_SCALE;
    long double halfh = 0.5 * h;

    long double hGMi = h * Config::G;
    for (auto i = 0; i < m_objs.size(); ++i) {

        auto &obj = m_objs[i];
        auto ri_x = obj.rx;
        auto ri_y = obj.ry;
        auto vi_x = obj.vx;
        auto vi_y = obj.vy;

        // f(t, r, v) = v
        // g(t, r, v) = G*Mi sum(j != i, Mj/|rj-r|^3 (rj-r)
        // k0 = h * f(ti, ri, vi) = hv
        long double k0_x = h * vi_x;
        long double k0_y = h * vi_y;

        // l0 = h * g(ti, ri, vi) = h*G*Mi*sum(j != i, Mj/|rj-ri|^3 (rj-ri)
        long double l0_x = 0;
        long double l0_y = 0;
        for (auto j = 0; j < m_objs.size(); ++j) {
            if (j == i) { continue; }
            auto &other = m_objs[j];
            long double delta_x = other.rx - ri_x;
            long double delta_y = other.ry - ri_y;
            long double distSq = delta_x * delta_x + delta_y * delta_y;
            long double dist = sqrt(distSq);
            long double distCub = dist * dist * dist;
            long double massFrac = other.mass / distCub;
            l0_x += massFrac * delta_x;
            l0_y += massFrac * delta_y;
        }
        l0_x *= hGMi;
        l0_y *= hGMi;


        // k1 = h * f(ti + h/2, ri + k0/2, vi + l0/2) = h(vi + l0/2)
        long double k1_x = k0_x + halfh * l0_x;
        long double k1_y = k0_y + halfh * l0_y;

        // l1 = h * g(..., ri + k0/2, ...)
        long double l1_x = 0;
        long double l1_y = 0;
        long double half_k0_x = 0.5 * k0_x;
        long double half_k0_y = 0.5 * k0_y;
        for (auto j = 0; j < m_objs.size(); ++j) {
            if (j == i) { continue; }
            auto &other = m_objs[j];
            long double delta_x = other.rx - ri_x - half_k0_x;
            long double delta_y = other.ry - ri_y - half_k0_y;
            long double distSq = delta_x * delta_x + delta_y * delta_y;
            long double dist = sqrt(distSq);
            long double distCub = dist * dist * dist;
            long double massFrac = other.mass / distCub;
            l1_x += massFrac * delta_x;
            l1_y += massFrac * delta_y;
        }
        l1_x *= hGMi;
        l1_y *= hGMi;

        // k2 = h(vi + l1/2)
        long double k2_x = k0_x + halfh * l1_x;
        long double k2_y = k0_y + halfh * l1_y;


        // l2 = h * g(..., ri + k1/2, ...)
        long double l2_x = 0;
        long double l2_y = 0;
        long double half_k1_x = 0.5 * k2_x;
        long double half_k1_y = 0.5 * k2_y;
        for (auto j = 0; j < m_objs.size(); ++j) {
            if (j == i) { continue; }
            auto &other = m_objs[j];
            long double delta_x = other.rx - ri_x - half_k1_x;
            long double delta_y = other.ry - ri_y - half_k1_y;
            long double distSq = delta_x * delta_x + delta_y * delta_y;
            long double dist = sqrt(distSq);
            long double distCub = dist * dist * dist;
            long double massFrac = other.mass / distCub;
            l2_x += massFrac * delta_x;
            l2_y += massFrac * delta_y;
        }
        l2_x *= hGMi;
        l2_y *= hGMi;

        // k3 = h(vi + l2)
        long double k3_x = k0_x + h * l2_x;
        long double k3_y = k0_y + h * l2_y;

        // l3 = h * g(..., ri + k2, ...)
        long double l3_x = 0;
        long double l3_y = 0;
        for (auto j = 0; j < m_objs.size(); ++j) {
            if (j == i) { continue; }
            auto &other = m_objs[j];
            long double delta_x = other.rx - ri_x - k2_x;
            long double delta_y = other.ry - ri_y - k2_y;
            long double distSq = delta_x * delta_x + delta_y * delta_y;
            long double dist = sqrt(distSq);
            long double distCub = dist * dist * dist;
            long double massFrac = other.mass / distCub;
            l3_x += massFrac * delta_x;
            l3_y += massFrac * delta_y;
        }
        l3_x *= hGMi;
        l3_y *= hGMi;

        obj.rx += (k0_x + 2 * k1_x + 2 * k2_x + k3_x) / 6;
        obj.ry += (k0_y + 2 * k1_y + 2 * k2_y + k3_y) / 6;
        obj.vx += (l0_x + 2 * l1_x + 2 * l2_x + l3_x) / 6;
        obj.vy += (l0_y + 2 * l1_y + 2 * l2_y + l3_y) / 6;

        *obj.px = Config::DISTANCE_SCALE * static_cast<GLfloat>(obj.rx);
        *obj.py = Config::DISTANCE_SCALE * static_cast<GLfloat>(obj.ry);
    }

    /*typedef long double ldbl;
    auto endIt = std::end(m_objs);
    for (auto &o : m_objs) {
        o.fx = 0;
        o.fy = 0;
    }
    for (auto i = std::begin(m_objs); i != endIt; ++i) {
        auto &oi = *i;
        for (auto j = std::next(i); j != endIt; ++j) {
            auto &oj = *j;
            ldbl dx = oj.rx - oi.rx;
            ldbl dy = oj.ry - oi.ry;
            ldbl rsq = dx * dx + dy * dy;
            ldbl r = sqrt(rsq);
            ldbl F = Config::G * oi.mass * oj.mass / rsq;
            ldbl fx = F * dx / r;
            ldbl fy = F * dy / r;
            oi.fx += fx;
            oi.fy += fy;
            oj.fx -= fx;
            oj.fy -= fy;
        }
        oi.ax = oi.fx / oi.mass;
        oi.ay = oi.fy / oi.mass;
        ldbl dtax = h * oi.ax;
        ldbl dtay = h * oi.ay;
        oi.rx += h * oi.vx + halfh * dtax;
        oi.ry += h * oi.vy + halfh * dtay;
        oi.vx += dtax;
        oi.vy += dtay;

        *oi.px = Config::DISTANCE_SCALE * oi.rx;
        *oi.py = Config::DISTANCE_SCALE * oi.ry;
    }*/
    /*for (auto i = 0; i < sz; ++i) {
        ldbl Fx = 0;
        ldbl Fy = 0;
        for (auto j = i; j < sz; ++j) {
            if (j == i) { continue; }
            ldbl dx = m_objs[j].rx - m_objs[i].rx;
            ldbl dy = m_objs[j].ry - m_objs[i].ry;
            ldbl r = sqrt(dx * dx + dy * dy);
            ldbl F = Config::G * m_objs[i].mass * m_objs[j].mass / r / r;
            Fx += F * dx / r;
            Fy += F * dy / r;
        }

        m_objs[i].ax = Fx / m_objs[i].mass;
        m_objs[i].ay = Fy / m_objs[i].mass;
        m_objs[i].vx += h * m_objs[i].ax;
        m_objs[i].vy += h * m_objs[i].ay;
        m_objs[i].rx += h * m_objs[i].vx;
        m_objs[i].ry += h * m_objs[i].vy;

        *m_objs[i].px = Config::DISTANCE_SCALE * m_objs[i].rx;
        *m_objs[i].py = Config::DISTANCE_SCALE * m_objs[i].ry;
    }*/

    /*for (auto &obj : m_objs) {
        obj.resetForce();
    }
    for (auto flIt = std::begin(m_objs); flIt != std::end(m_objs); ++flIt) {
        for (auto slIt = std::next(flIt); slIt != std::end(m_objs); ++slIt) {
            flIt->addGravity(*slIt);
        }
    }
    for (auto &obj : m_objs) {
        obj.step(h);
    }*/
}

RendererInterface Engine::getParams() const {
    return {
        .objCoords = m_objCoords.data(),
        .objRadii = m_objRadii.data(),
        .numObjs = m_objs.size(),
    };
}
