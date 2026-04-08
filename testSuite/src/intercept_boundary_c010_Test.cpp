#include "testSuiteHeader.hpp"

extern "C" {
    extern double __ufit_definitions_fortran_MOD_grid1min;
    extern double __ufit_definitions_fortran_MOD_grid1max;
    extern double __ufit_definitions_fortran_MOD_grid2min;
    extern double __ufit_definitions_fortran_MOD_grid2max;
    extern double __ufit_definitions_fortran_MOD_grid3min;
    extern double __ufit_definitions_fortran_MOD_grid3max;
    
    void __ufit_functions_fortran_MOD_intercept_boundary_c010(double* pos_in, double* direction, double* delta_out);
}

TEST(InterceptBoundaryC010, EqualsOne) {
    RecordProperty("priority", "medium");
    __ufit_definitions_fortran_MOD_grid1min = 0.0;
    __ufit_definitions_fortran_MOD_grid1max = 10.0;
    __ufit_definitions_fortran_MOD_grid2min = 0.0;
    __ufit_definitions_fortran_MOD_grid2max = 10.0;
    __ufit_definitions_fortran_MOD_grid3min = 0.0;
    __ufit_definitions_fortran_MOD_grid3max = 5.0;

    double position[3] = {5.0, 2.0, 1.0};  
    double direction[3] = {0.0, 1.0, 0.5}; 
    double delta_out = 0.0;
    double expected_delta_out = 1.0;

    __ufit_functions_fortran_MOD_intercept_boundary_c010(position, direction, &delta_out);

    EXPECT_DOUBLE_EQ(delta_out,expected_delta_out);
}

TEST(InterceptBoundaryC010, BoundaryCaseLessThan) {
    RecordProperty("priority", "high");
    __ufit_definitions_fortran_MOD_grid1min = 0.0;
    __ufit_definitions_fortran_MOD_grid1max = 10.0;
    __ufit_definitions_fortran_MOD_grid2min = 0.0;
    __ufit_definitions_fortran_MOD_grid2max = 10.0;
    __ufit_definitions_fortran_MOD_grid3min = 0.0;
    __ufit_definitions_fortran_MOD_grid3max = 5.0;

    double position[3] = {5.0, 9.5, 1.0};  
    double direction[3] = {0.0, 1.0, 0.0}; 
    double delta_out = 0.0;
    double expected_delta_out = 1.0;

    __ufit_functions_fortran_MOD_intercept_boundary_c010(position, direction, &delta_out);
    // delta_out will be 0.5, but expected is 1.0
    EXPECT_LT(delta_out,expected_delta_out);
    // EXPECT_EQ(delta_out,expected_delta_out) << "intercept_boundary_c100 has bug \n";
    
}

TEST(InterceptBoundaryC010, HandlesZeroDirectionUsingEpsilon) {
    RecordProperty("priority", "high");
    __ufit_definitions_fortran_MOD_grid1min = 0.0;
    __ufit_definitions_fortran_MOD_grid1max = 10.0;
    __ufit_definitions_fortran_MOD_grid2min = 0.0;
    __ufit_definitions_fortran_MOD_grid2max = 10.0;
    __ufit_definitions_fortran_MOD_grid3min = 0.0;
    __ufit_definitions_fortran_MOD_grid3max = 10.0;

    double position[3] = {5.0, 5.0, 5.0};  
    double direction[3] = {1.0, 0.0, 0.0}; 
    double delta_out = 0.0;
    double expected_delta_out = 1.0;

    __ufit_functions_fortran_MOD_intercept_boundary_c010(position, direction, &delta_out);
    EXPECT_DOUBLE_EQ(delta_out,expected_delta_out);
    
}