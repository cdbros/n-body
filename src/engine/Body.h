#pragma once

#include <QOpenGLFunctions>
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
