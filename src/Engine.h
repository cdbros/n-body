#pragma once

#include <QOpenGLFunctions>
#include <QThread>
#include <vector>

class Body {
    friend class Engine;

  public:
    struct Params {
        inline explicit Params(long double x0 = 0, long double y0 = 0, long double vx0 = 0, long double vy0 = 0,
                               long double mass = 0, long double radius = 0)
            : x0{x0}, y0{y0}, vx0{vx0}, vy0{vy0}, mass{mass}, radius{radius} {}

        long double x0, y0;
        long double vx0, vy0;
        long double mass;
        long double radius;
    };

  private:
    explicit Body(const Params &params);

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
    long double radius;

    std::vector<GLfloat>::iterator px;
    std::vector<GLfloat>::iterator py;
};

struct RendererInterface {
    const GLfloat *objCoords;
    const GLfloat *objRadii;
    std::size_t numObjs;
};

class Engine {
  public:
    Engine();

  public:
    void addObject(const Body::Params &params);
    void step(unsigned tickStep);
    [[nodiscard]] RendererInterface getParams() const;

  private:
    std::vector<Body> m_objs;
    std::vector<GLfloat> m_objCoords;
    std::vector<GLfloat> m_objRadii;
    GLfloat m_zIndex;
};

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
