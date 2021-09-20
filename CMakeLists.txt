cmake_minimum_required(VERSION 3.3)
project(Tether)

set(CMAKE_CXX_STANDARD 17)

################################################################################
# Looking for IBEX
################################################################################

	find_package(IBEX REQUIRED)
	ibex_init_common() # IBEX should have installed this function
	message(STATUS "Found IBEX version ${IBEX_VERSION}")

	find_package(CODAC REQUIRED)
	message(STATUS "Found Tubex version ${TUBEX_VERSION}")


################################################################################
# Looking for Eigen3
################################################################################

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