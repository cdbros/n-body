#include "Engine.h"
#include "Config.h"

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

void Engine::step(unsigned tickStep) {
    constexpr long double usec_to_sec = 1.0e+6;
    long double dt = tickStep / usec_to_sec * Config::TIME_SCALE;
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

RendererInterface Engine::getParams() const {
    return {
        .objCoords = m_objCoords.data(),
        .objRadii = m_objRadii.data(),
        .numObjs = m_objs.size(),
    };
}
