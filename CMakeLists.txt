cmake_minimum_required(VERSION 3.3)
project(Tether)

set(CMAKE_CXX_STANDARD 11)

find_package(ignition-math6 REQUIRED)
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
    QUIET
)

include(${VTK_USE_FILE})

add_library(TetherElement src/TetherElement.cpp)
target_include_directories(TetherElement PUBLIC include)
target_link_libraries(TetherElement ignition-math6::ignition-math6 ${VTK_LIBRARIES})

add_library(Tether src/Tether.cpp)
target_include_directories(Tether PUBLIC include)
target_link_libraries(Tether TetherElement ignition-math6::ignition-math6)

add_library(vtxTetherFigure src/vtxTetherFigure.cpp)
target_include_directories(vtxTetherFigure PUBLIC include)
target_link_libraries(vtxTetherFigure TetherElement ignition-math6::ignition-math6 ${VTK_LIBRARIES})

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