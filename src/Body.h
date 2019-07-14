#include <string_view>

enum class Colour {
    red,
    blue,
    green,
    purple
};

class Body {

    public:
        /// Constructor to Create and Initialize a new Body.
        Body(double rx, double ry, double vx, double vy, double mass, Colour colour);

        /// update the velocity and position using a timestep dt
        void Update(double dt);

        /// returns the distance between two bodies
        double DistanceTo(Body b);

        /// Set the force to 0 for the next iteration
        void ResetForce();

        /// compute the net force acting between the body a and b, and
        /// add to the net force acting on a
        void AddForce(const Body & b);

        /// Convert to string format.
        std::string_view ToString();

    private :

        static constexpr double G = 6.673e-11;   // gravitational constant
        static constexpr double solarmass = 1.98892e30;

        /// holds the cartesian positions
        double rx, ry;

        /// velocity components
        double vx, vy;

        /// force components
        double fx, fy;

        double mass;

        Colour colour;

};
