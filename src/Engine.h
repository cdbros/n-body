#pragma once

#include <QThread>
#include <QOpenGLFunctions>
#include <vector>

class Body {
    friend class Engine;

  public:
    struct Params {
        long double x0, y0;
        long double vx0, vy0;
        long double mass;
    };

  private:
    Body(const Params &params);

  private:
    void step(long double dt);
    void resetForce();
    void addGravity(Body &b);

  private:
    long double rx, ry;
    long double vx, vy;
    long double ax, ay;
    long double fx, fy;
    long double mass;

    std::vector<GLfloat>::iterator px;
    std::vector<GLfloat>::iterator py;
};

class Engine {
  public:
    Engine();

  public:
    void addObject(const Body::Params &params);
    void step(unsigned long long ticks, unsigned tickStep);
    const GLfloat *getObjCoords() const;
    std::size_t getNumObjs() const;

  private:
    std::vector<Body> m_objs;
    std::vector<GLfloat> m_objCoords;
    GLfloat m_zIndex;
};

class EngineThread : public QThread {
    Q_OBJECT

  private:
    void run() override;

  public:
    EngineThread(unsigned tickStep = 20);

    inline void stopEngine() { m_shouldRun = false; }

  signals:
    void renderReady(const GLfloat *objCoords, std::size_t numObjs);

  private:
    Engine m_engine;
    unsigned m_tickStep;
    bool m_shouldRun;
    bool m_rateLimit;
};
