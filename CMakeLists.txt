cmake_minimum_required(VERSION 3.3)
project(Tether)

set(CMAKE_CXX_STANDARD 17)

find_package(ignition-math6 REQUIRED)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

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

add_library(PID src/PID.cpp)
target_include_directories(PID PUBLIC include)

add_library(TetherElement src/TetherElement.cpp) 
target_include_directories(TetherElement PUBLIC include)
target_link_libraries(TetherElement Eigen3::Eigen ${VTK_LIBRARIES} PID)

add_library(Tether src/Tether.cpp)
target_include_directories(Tether PUBLIC include)
target_link_libraries(Tether TetherElement Eigen3::Eigen PID GSL::gsl)

add_library(vtkTetherFigure src/vtkTetherFigure.cpp)
target_include_directories(vtkTetherFigure PUBLIC include)
target_link_libraries(vtkTetherFigure TetherElement Eigen3::Eigen ${VTK_LIBRARIES})


add_subdirectory(examples)
add_subdirectory(tests)

option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
	# set input and output files
	set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
	set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	# request to configure the file
	configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
	message("Doxygen build started")

	# note the option ALL which allows to build the docs together with the application
	add_custom_target( doc_doxygen ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)