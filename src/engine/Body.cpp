#include "Body.h"
#include "Config.h"
#include <cmath>

Body::Body(const Params &params)
    : rx(params.x0), ry(params.y0), vx(params.vx0), vy(params.vy0), ax(0), ay(0), fx(0), fy(0), mass(params.mass),
      radius(params.radius) {}

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
    *px = static_cast<GLfloat>(Config::DISTANCE_SCALE * rx);
    *py = static_cast<GLfloat>(Config::DISTANCE_SCALE * ry);
}

void Body::resetForce() {
    fx = 0;
    fy = 0;
}

void Body::addGravity(Body &b) {
    long double dx = b.rx - rx;
    long double dy = b.ry - ry;
    long double distSq = dx * dx + dy * dy;
    long double fg = Config::G * mass * b.mass / distSq;
    long double dist = sqrt(distSq);
    long double fgx = fg * dx / dist;
    long double fgy = fg * dy / dist;
    fx += fgx;
    fy += fgy;
    b.fx -= fgx;
    b.fy -= fgy;
}
