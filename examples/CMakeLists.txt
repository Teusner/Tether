cmake_minimum_required(VERSION 3.3)
project(tether_examples)

add_executable(example_101 example_101.cpp)
target_include_directories(example_101 PUBLIC ../src/core ../src/graphics)
target_link_libraries(example_101 Tether vtkTetherFigure)

add_executable(TetherElementExample core/TetherElementExample.cpp)
target_include_directories(TetherElementExample PUBLIC ../src/core)
target_link_libraries(TetherElementExample TetherElement)

add_executable(TetherExample core/TetherExample.cpp)
target_include_directories(TetherExample PUBLIC ../src/core)
target_link_libraries(TetherExample Tether TetherElement)

add_executable(CtcTetherExample interval/CtcTetherExample.cpp)
target_include_directories(CtcTetherExample PUBLIC ../src/interval ../src/graphics)
target_link_libraries(CtcTetherExample PUBLIC Tether CtcTether vibes Ibex::ibex)

# add_executable(main main.cpp)
# target_link_libraries(main Tether TetherElement vtkTetherFigure ${VTK_LIBRARIES})