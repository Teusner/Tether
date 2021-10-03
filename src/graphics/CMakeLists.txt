add_library(vibes vibes.cpp vibes.hpp)

add_library(TetherFigure TetherFigure.cpp TetherFigure.hpp)
target_include_directories(TetherFigure PUBLIC ../core)
target_link_libraries(TetherFigure Tether vibes)

add_library(VIBesTetherFigure VIBesTetherFigure.cpp VIBesTetherFigure.hpp)
target_include_directories(VIBesTetherFigure PUBLIC ../core)
target_link_libraries(VIBesTetherFigure Tether TetherElement Eigen3::Eigen)

add_library(vtkTetherFigure vtkTetherFigure.cpp vtkTetherFigure.hpp)
target_include_directories(vtkTetherFigure PUBLIC ../core)
target_link_libraries(vtkTetherFigure TetherElement Eigen3::Eigen ${VTK_LIBRARIES})