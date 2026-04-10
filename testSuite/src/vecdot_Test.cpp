#include "testSuiteHeader.hpp"

/*
    function vecdot(v1,v2)
        REAL(num) :: v1(3), v2(3)
        REAL(num) :: vecdot
        vecdot = v1(1)*v2(1)+v1(2)*v2(2)+v1(3)*v2(3)
    end function vecdot
*/

extern "C" {
    double __ufit_functions_fortran_MOD_vecdot(double *vec1, double *vec2);
} 

TEST(Vecdot, NormalCase) {

    double vec1[3]={1.0,2.0,3.0};
	double vec2[3]={4.0,5.0,6.0};
    double expected_dot_prod = 32.0;
	double c = __ufit_functions_fortran_MOD_vecdot(vec1,vec2);
    EXPECT_DOUBLE_EQ(c,expected_dot_prod) << "Vecdot function has bugs\n";
}

TEST(Vecdot, Orthogonal) {

    double vec1[3]={1.0,0.0,0.0};
	double vec2[3]={0.0,1.0,0.0};
    double expected_dot_prod = 0.0;
	double c = __ufit_functions_fortran_MOD_vecdot(vec1,vec2);
    EXPECT_DOUBLE_EQ(c,expected_dot_prod) << "Vecdot function has bugs\n";
}

TEST(Vecdot, NegativeAndPrecision) {
    RecordProperty("priority", "high");
    // Testing negative decimals
    double vec1[3] = {-1.5, 2.5, 0.0};
    double vec2[3] = {2.0, 4.0, -10.0};
    double expected = 7.0;
    
    double result = __ufit_functions_fortran_MOD_vecdot(vec1, vec2);
    EXPECT_NEAR(result, expected, 1e-12);
}

TEST(Vecdot, ZeroVector) {
    RecordProperty("priority", "high");
    double vec1[3] = {0.0, 0.0, 0.0};
    double vec2[3] = {999.9, -123.4, 55.0};
    double expected = 0.0;
    
    double result = __ufit_functions_fortran_MOD_vecdot(vec1, vec2);
    EXPECT_DOUBLE_EQ(result, expected);
}