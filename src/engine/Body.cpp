#include "Body.h"
#include <cmath>

Body::Body(const Params &params)
    : rx(params.x0), ry(params.y0), vx(params.vx0), vy(params.vy0), ax(0), ay(0), fx(0), fy(0), mass(params.mass),
      radius(params.radius) {}

void Body::step(engine_fp_t dt) {
    // Do calculations in higher precision
    ax = fx / mass;
    ay = fy / mass;

    // 4th order Runge-Kutta for (d/dt)^2 r = F/m
    engine_fp_t halfdt = 0.5 * dt;
    engine_fp_t dtax = dt * ax;
    engine_fp_t dtay = dt * ay;
    rx += dt * vx + halfdt * dtax;
    ry += dt * vy + halfdt * dtay;
    vx += dtax;
    vy += dtay;

    // Write to coordinate array
    *px = static_cast<GLfloat>(Config::DISTANCE_SCALE * rx);
    *py = static_cast<GLfloat>(Config::DISTANCE_SCALE * ry);
}

void Body::resetForce() {
    fx = 0;
    fy = 0;
}

void Body::addGravity(Body &b) {
    engine_fp_t dx = b.rx - rx;
    engine_fp_t dy = b.ry - ry;
    engine_fp_t distSq = dx * dx + dy * dy;
    engine_fp_t fg = Config::G * mass * b.mass / distSq;
    engine_fp_t dist = sqrt(distSq);
    engine_fp_t fgx = fg * dx / dist;
    engine_fp_t fgy = fg * dy / dist;
    fx += fgx;
    fy += fgy;
    b.fx -= fgx;
    b.fy -= fgy;
}
