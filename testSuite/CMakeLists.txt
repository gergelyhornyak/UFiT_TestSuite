cmake_minimum_required(VERSION 3.14)
project(testSuite LANGUAGES CXX Fortran)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")

set(UFIT_DIR "/ProjectDir/target/UFiT")
set(OBJECT_FILES
    ${UFIT_DIR}/UFiT_Definitions_Fortran.o
    ${UFIT_DIR}/UFiT_User_Functions.o
    ${UFIT_DIR}/UFiT_Functions_Fortran.o
)

enable_language(Fortran)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)    
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

add_executable(TestHub src/TestHub.cpp src/BlackBoxTest.cpp src/GreyBoxTest.cpp src/RegressionTest.cpp src/testSuiteHeader.cpp)
target_link_libraries(TestHub PRIVATE GTest::gtest GTest::gtest_main)
target_include_directories(TestHub PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

