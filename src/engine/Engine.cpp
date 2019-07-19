#include "Engine.h"
#include <cmath>
#include <algorithm>
#include <functional>

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

typedef decltype(getTimeUsec()) usec_t;
static usec_t start, stop;
static usec_t total = 0;
static unsigned frameCount = 0;

void Engine::metricsStart() {
    start = getTimeUsec();
}

void Engine::metricsStop() {
    stop = getTimeUsec();
    total += stop - start;
    ++frameCount;
    if (frameCount == 10000000) {
        std::cout << "Time: " << total / 1e+6 << " sec" << std::endl;
        std::cout << "FPS:  " << frameCount / (total / 1e+6) << std::endl;
        std::cout << "obj[3]:" << std::endl;
        auto &obj = m_objs[3];
        std::cout << "   rx: " << obj.rx << std::endl;
        std::cout << "   ry: " << obj.ry << std::endl;
        std::cout << "   vx: " << obj.vx << std::endl;
        std::cout << "   vy: " << obj.vy << std::endl;
        exit(0);
    }
}

void Engine::step(unsigned tickStep) {
    metricsStart();

    constexpr engine_fp_t usec_to_sec = 1.0e+6;
    engine_fp_t h = tickStep / usec_to_sec * Config::TIME_SCALE;
    engine_fp_t halfh = 0.5 * h;

    engine_fp_t hGMi = h * Config::G;

    for (auto i = 0; i < m_objs.size(); ++i) {

        auto &o_i = m_objs[i];

        engine_fp_t hvx = o_i.vx * h;
        engine_fp_t hvy = o_i.vy * h;
        engine_fp_t acc_lx = 0;
        engine_fp_t acc_ly = 0;

        engine_fp_t lx = 0;
        engine_fp_t ly = 0;
        engine_fp_t kx = 0;
        engine_fp_t ky = 0;

        // k0
        engine_fp_t ri_x = o_i.rx;
        engine_fp_t ri_y = o_i.ry;
        kx = hvx;
        ky = hvy;
        engine_fp_t acc_kx = kx;
        engine_fp_t acc_ky = ky;
        //<

        // l0
        for (auto j = 0; j < m_objs.size(); ++j) {
            if (j == i) { continue; }
            auto &o_j = m_objs[j];
            engine_fp_t dx = o_j.rx - ri_x;
            engine_fp_t dy = o_j.ry - ri_y;
            engine_fp_t distSq = dx * dx + dy * dy;
            engine_fp_t massFrac = o_j.mass / distSq / sqrt(distSq);
            lx += massFrac * dx;
            ly += massFrac * dy;
        }
        lx *= hGMi;
        ly *= hGMi;
        acc_lx += lx;
        acc_ly += ly;
        //<

        // k1
        ri_x += kx * 0.5;
        ri_y += ky * 0.5;
        kx = hvx + halfh * lx;
        ky = hvy + halfh * ly;
        acc_kx += 2 * kx;
        acc_ky += 2 * ky;
        //<

        // l1
        lx = 0;
        ly = 0;
        for (auto j = 0; j < m_objs.size(); ++j) {
            if (j == i) { continue; }
            auto &o_j = m_objs[j];
            engine_fp_t dx = o_j.rx - ri_x;
            engine_fp_t dy = o_j.ry - ri_y;
            engine_fp_t distSq = dx * dx + dy * dy;
            engine_fp_t massFrac = o_j.mass / distSq / sqrt(distSq);
            lx += massFrac * dx;
            ly += massFrac * dy;
        }
        lx *= hGMi;
        ly *= hGMi;
        acc_lx += 2 * lx;
        acc_ly += 2 * ly;
        //<

        // k2
        ri_x = o_i.rx + kx * 0.5;
        ri_y = o_i.ry + ky * 0.5;
        kx = hvx + halfh * lx;
        ky = hvy + halfh * ly;
        acc_kx += 2 * kx;
        acc_ky += 2 * ky;
        //<

        // l2
        lx = 0;
        ly = 0;
        for (auto j = 0; j < m_objs.size(); ++j) {
            if (j == i) { continue; }
            auto &o_j = m_objs[j];
            engine_fp_t dx = o_j.rx - ri_x;
            engine_fp_t dy = o_j.ry - ri_y;
            engine_fp_t distSq = dx * dx + dy * dy;
            engine_fp_t massFrac = o_j.mass / distSq / sqrt(distSq);
            lx += massFrac * dx;
            ly += massFrac * dy;
        }
        lx *= hGMi;
        ly *= hGMi;
        acc_lx += 2 * lx;
        acc_ly += 2 * ly;
        //<

        // k3
        ri_x = o_i.rx + kx;
        ri_y = o_i.ry + ky;
        kx = hvx + halfh * lx;
        ky = hvy + halfh * ly;
        acc_kx += kx;
        acc_ky += ky;
        //<

        // l3
        lx = 0;
        ly = 0;
        for (auto j = 0; j < m_objs.size(); ++j) {
            if (j == i) { continue; }
            auto &o_j = m_objs[j];
            engine_fp_t dx = o_j.rx - ri_x;
            engine_fp_t dy = o_j.ry - ri_y;
            engine_fp_t distSq = dx * dx + dy * dy;
            engine_fp_t massFrac = o_j.mass / distSq / sqrt(distSq);
            lx += massFrac * dx;
            ly += massFrac * dy;
        }
        lx *= hGMi;
        ly *= hGMi;
        acc_lx += lx;
        acc_ly += ly;
        //<

        o_i.rx += acc_kx / 6;
        o_i.ry += acc_ky / 6;
        o_i.vx += acc_lx / 6;
        o_i.vy += acc_ly / 6;

        *o_i.px = Config::DISTANCE_SCALE * o_i.rx;
        *o_i.py = Config::DISTANCE_SCALE * o_i.ry;
    }

    /*typedef engine_fp_t ldbl;
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

    metricsStop();
}

RendererInterface Engine::getParams() const {
    return {
        .objCoords = m_objCoords.data(),
        .objRadii = m_objRadii.data(),
        .numObjs = m_objs.size(),
    };
}
