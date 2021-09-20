add_library(vibes vibes.cpp vibes.hpp)

add_library(vtkTetherFigure vtkTetherFigure.cpp vtkTetherFigure.hpp)
target_include_directories(vtkTetherFigure PUBLIC ../core)
target_link_libraries(vtkTetherFigure TetherElement Eigen3::Eigen ${VTK_LIBRARIES})