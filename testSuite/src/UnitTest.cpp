#include "testSuiteHeader.hpp"

extern "C" float __ufit_functions_fortran_MOD_vecdot(float *vec1, float *vec2);

TEST(TestUTUFiTFunction, TestVecdot) {

    float a[3]={1,2,3};
	float b[3]={4,5,6};
    float expectedValueC = 32;
	float c = __ufit_functions_fortran_MOD_vecdot(a,b);
    printf("a(%f,%f,%f) * b(%f,%f,%f) = %f\n",
        a[0],a[1],a[2],
        b[0],b[1],b[2],
        c);
    EXPECT_EQ(c,expectedValueC) << "Vecdot function has bugs: " << c << "\n";
    
}