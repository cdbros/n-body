#pragma once

#include "Body.h"
#include "RendererInterface.h"

class Engine {
  public:
    Engine();

  public:
    void addObject(const Body::Params &params);
    void step(unsigned tickStep);
    void takeMetrics();
    [[nodiscard]] RendererInterface getParams() const;

  private:
    std::vector<Body> m_objs;
    std::vector<GLfloat> m_objCoords;
    std::vector<GLfloat> m_objRadii;
    GLfloat m_zIndex;

    long double m_lastTime{};
    std::size_t m_frameCount{};
};
