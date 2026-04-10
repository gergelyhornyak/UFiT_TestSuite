cmake_minimum_required(VERSION 3.14)
project(testSuite LANGUAGES CXX Fortran)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")

set(UFIT_DIR "/ProjectDir/target/UFiT")

add_library(UFiT_Fortran_Lib STATIC
    ${UFIT_DIR}/UFiT_Definitions_Fortran.F90
    ${UFIT_DIR}/UFiT_User_Functions.F90
    ${UFIT_DIR}/UFiT_Functions_Fortran.F90
    ${UFIT_DIR}/UFiT_Python_Callable.F90
)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(TestHub 
    src/TestHub.cpp 
    #src/BlackBoxTest.cpp 
    #src/GreyBoxTest.cpp 
    #src/RegressionTest.cpp 
    src/initialize_variables_Test.cpp
    src/intercept_boundary_c100_Test.cpp
    src/intercept_boundary_c010_Test.cpp
    src/vecdot_Test.cpp
    src/normalize_vector_Test.cpp
    src/normalize_vector_binding.f90
    src/find_index_Test.cpp
    src/find_index_binding.f90
    src/find_index_irregular_Test.cpp
    src/setup_find_index_irregular.f90
    src/find_index_irregular_binding.f90
    src/testSuiteHeader.cpp
)
target_link_libraries(TestHub PRIVATE
    GTest::gtest
    GTest::gtest_main
    gfortran
    UFiT_Fortran_Lib
)
target_include_directories(TestHub PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

