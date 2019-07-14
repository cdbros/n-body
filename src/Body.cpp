#include <cmath>
#include <sstream>

#include "Body.h"

Body::Body(double rx, double ry, double vx, double vy, double mass, Colour colour)
    : rx {rx} , ry {ry} , vx {vx} , vy {vy} , mass {mass} , colour{colour} {}

    // update the velocity and position using a timestep dt
    void Body::Update(double dt) {
        vx += dt * (fx / mass);
        vy += dt * (fy / mass);
        rx += dt * vx;
        ry += dt * vy;
    }

double Body::DistanceTo(Body b) {
    double dx = rx - b.rx;
    double dy = ry - b.ry;
    return sqrt((dx * dx) + (dy * dy));
}

void Body::ResetForce() {
    fx = 0.0;
    fy = 0.0;
}

void Body::AddForce(const Body & b) {
    // softening parameter (to avoid infinities).
    double EPS = 3E4;

    double dx = b.rx - rx;
    double dy = b.ry - ry;

    double dist = sqrt((dx * dx) + (dy * dy));
    double F = ((G * mass) * b.mass) / ((dist * dist) + (EPS * EPS));

    fx += F * (dx / dist);
    fy += F * (dy / dist);
}

std::string_view Body::ToString() {
    return  std::to_string(rx) + ", " +
            std::to_string(ry) + ", " +
            std::to_string(vx) + ", " +
            std::to_string(vy) + ", " +
            std::to_string(mass);
}

