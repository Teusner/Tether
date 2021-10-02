add_library(CtcTether CtcTether.cpp)
target_include_directories(CtcTether PUBLIC ../core)
target_link_libraries(CtcTether PUBLIC Tether Ibex::ibex)