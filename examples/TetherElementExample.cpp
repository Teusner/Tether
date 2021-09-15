//! [example]
#include "tether/TetherElement.hpp"

#include <cstdlib>
#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace tether;

int main(int, char*[]) {
    // TetherElement parameters
    std::double_t mass = 0.5;
    std::double_t volume = 0.1;
    std::double_t length = 0.02;
    Eigen::Vector3d X0(1.0, 2.0, 3.0);

    // Create a TetherElement
    TetherElement tether_element(mass, volume, length, X0);

    // Accessing TetherElement parameters
    std::cout << ">> TetherElement parameters" << std::endl;
    std::cout << "mass \t: " << tether_element.Mass() << std::endl;
    std::cout << "volume \t: " << tether_element.Volume() << std::endl;
    std::cout << "length \t: " << tether_element.Length() << std::endl;

    // Accessing TetherElement state
    std::cout << ">> TetherElement state" << std::endl;
    std::cout << "x \t: " << tether_element.X() << std::endl;
    std::cout << "y \t: " << tether_element.Y() << std::endl;
    std::cout << "z \t: " << tether_element.Z() << std::endl;

    // Update the state from t to t + h
    std::double_t h = 0.01;
    tether_element.Step(h);

    return EXIT_SUCCESS;
}
//! [example]