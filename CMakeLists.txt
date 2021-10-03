cmake_minimum_required(VERSION 3.3)
project(Tether)

set(CMAKE_CXX_STANDARD 17)

find_package(IBEX REQUIRED)
ibex_init_common()
message(STATUS "Found IBEX version ${IBEX_VERSION}")

find_package(CODAC REQUIRED)
message(STATUS "Found Tubex version ${TUBEX_VERSION}")

find_package(Eigen3 REQUIRED NO_MODULE)
message(STATUS "Found Eigen3 version ${EIGEN3_VERSION}")
add_definitions(${EIGEN3_DEFINITIONS})
include_directories(${EIGEN3_INCLUDE_DIRS})

find_package(GSL REQUIRED)

find_package(VTK COMPONENTS
	vtkCommonColor
	vtkCommonCore
	vtkFiltersSources
	vtkInteractionStyle
	vtkRenderingContextOpenGL2
	vtkRenderingCore
	vtkRenderingFreeType
	vtkRenderingGL2PSOpenGL2
	vtkRenderingOpenGL2
)

include(${VTK_USE_FILE})

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)