cmake_minimum_required(VERSION 3.3)
project(tether_examples)

add_executable(example_101 example_101.cpp)
target_link_libraries(example_101 Tether vtkTetherFigure)

add_executable(TetherElementExample TetherElementExample.cpp)
target_link_libraries(TetherElementExample TetherElement)

add_executable(TetherExample TetherExample.cpp)
target_link_libraries(TetherExample Tether TetherElement)

add_executable(CtcTetherExample CtcTetherExample.cpp)
target_compile_options(CtcTetherExample PUBLIC ${CODAC_CXX_FLAGS})
target_include_directories(CtcTetherExample SYSTEM PUBLIC ${CODAC_INCLUDE_DIRS})
target_link_libraries(CtcTetherExample PUBLIC Tether CtcTether ${CODAC_LIBRARIES} Ibex::ibex ${CODAC_LIBRARIES})

# add_executable(main main.cpp)
# target_link_libraries(main Tether TetherElement vtkTetherFigure ${VTK_LIBRARIES})