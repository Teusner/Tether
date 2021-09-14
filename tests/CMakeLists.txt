cmake_minimum_required(VERSION 3.3)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(TetherElementTest TetherElementTest.cpp)
target_include_directories(TetherElementTest PUBLIC ../include)
target_link_libraries(TetherElementTest gtest_main TetherElement)
add_test(NAME tether_element_test COMMAND TetherElementTest)

add_executable(TetherTest TetherTest.cpp)
target_include_directories(TetherTest PUBLIC ../include)
target_link_libraries(TetherTest gtest_main Tether)
add_test(NAME tether_test COMMAND TetherTest)

include(GoogleTest)
gtest_discover_tests(TetherTest)
