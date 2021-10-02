add_library(PID PID.cpp PID.hpp)

add_library(TetherElement TetherElement.cpp TetherElement.hpp) 
target_link_libraries(TetherElement Eigen3::Eigen PID)

add_library(Tether Tether.cpp Tether.hpp)
target_link_libraries(Tether TetherElement Eigen3::Eigen PID GSL::gsl)