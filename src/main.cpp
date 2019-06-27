#include <iostream>
#include "Body.h"

int main() {

    std::cout << "The Gamer Word of Bodies Begins" << std::endl;

    Body a = Body(23, 22, 3, 3, 2, Colour::green);

    Body b = Body(23.2323, 23.2323, 23.2323, 23.2323, 23.2323, Colour::blue);

    b.AddForce(a);

    std::cout << "a : " << a.ToString() << std::endl;
    std::cout << "b : " << b.ToString() << std::endl;

}
