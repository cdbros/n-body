#pragma once

#include "Config.h"
#include <QOpenGLFunctions>
#include <vector>

class Body {
    friend class Engine;

  public:
    struct Params {
        inline explicit Params(engine_fp_t x0 = 0, engine_fp_t y0 = 0, engine_fp_t vx0 = 0, engine_fp_t vy0 = 0,
                               engine_fp_t mass = 0, engine_fp_t radius = 0)
            : x0{x0}, y0{y0}, vx0{vx0}, vy0{vy0}, mass{mass}, radius{radius} {}

        engine_fp_t x0, y0;
        engine_fp_t vx0, vy0;
        engine_fp_t mass;
        engine_fp_t radius;
    };

  private:
    explicit Body(const Params &params);

  private:
    void step(engine_fp_t dt);
    void resetForce();
    void addGravity(Body &b);

  private:
    engine_fp_t rx, ry;
    engine_fp_t vx, vy;
    engine_fp_t ax, ay;
    engine_fp_t fx, fy;
    engine_fp_t mass;
    engine_fp_t radius;

    std::vector<GLfloat>::iterator px;
    std::vector<GLfloat>::iterator py;
};
