#include <cmath>
#include <sstream>
#include <string_view>

enum class Colour {
    red,
    blue,
    green,
    purple
};

class Body {
    private :
        static constexpr double G = 6.673e-11;   // gravitational constant
        static constexpr double solarmass = 1.98892e30;

        double rx, ry;       // holds the cartesian positions
        double vx, vy;       // velocity components
        double fx, fy;       // force components
        double mass;         // mass
        Colour colour;       // colour (for fun)

    public:
        // create and initialize a new Body
        Body(double rx, double ry, double vx, double vy, double mass, Colour colour)
            : rx {rx} , ry {ry} , vx {vx} , vy {vy} , mass {mass} , colour{colour} { }

        // update the velocity and position using a timestep dt
        void Update(double dt) {
            vx += dt * fx / mass;
            vy += dt * fy / mass;
            rx += dt * vx;
            ry += dt * vy;
        }

        // returns the distance between two bodies
        double DistanceTo(Body b) {
            double dx = rx - b.rx;
            double dy = ry - b.ry;
            return sqrt(dx*dx + dy*dy);
        }

        // set the force to 0 for the next iteration
        void ResetForce() {
            fx = 0.0;
            fy = 0.0;
        }

        // compute the net force acting between the body a and b, and
        // add to the net force acting on a
        void AddForce(const Body & b) {
            double EPS = 3E4;      // softening parameter (just to avoid infinities)
            double dx = b.rx - rx;
            double dy = b.ry - ry;
            double dist = sqrt((dx * dx) + (dy * dy));
            double F = ((G * mass) * b.mass) / ((dist * dist) + (EPS * EPS));
            fx += F * dx / dist;
            fy += F * dy / dist;
        }

        // convert to string representation formatted nicely
        std::string_view ToString() {
            return  std::to_string(rx) + ", " +
                    std::to_string(ry) + ", " +
                    std::to_string(vx) + ", " +
                    std::to_string(vy) + ", " +
                    std::to_string(mass);
        }
};
