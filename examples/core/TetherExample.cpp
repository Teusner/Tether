//! [example]
#include "Tether.hpp"
#include "TetherElement.hpp"


#include <cstdlib>
#include <iostream>

using namespace tether;

int main(int, char*[]) {
    // Tether parameters
    std::double_t length = 10;
    std::size_t n = 100;

    // Create a Tether
    Tether tether(length, n);

    // Accessing Tether parameters
    std::cout << ">> Tether parameters" << std::endl;
    std::cout << "n \t: " << tether.N() << std::endl;
    std::cout << "length \t: " << tether.Length() << std::endl;

    // Update the state from t to t + h
    std::double_t h = 0.01;
    tether.Step(h);

    return EXIT_SUCCESS;
}
//! [example]