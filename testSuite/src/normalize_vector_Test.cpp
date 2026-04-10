#include "testSuiteHeader.hpp"

/*
    function normalize_vector(vec_in)
        REAL(num) :: vec_in(3)
        REAL(num) :: normalize_vector(3)
        normalize_vector(:) = vec_in(:)/SQRT(vec_in(1)**2+vec_in(2)**2+vec_in(3)**2)
    end function normalize_vector
*/

extern "C" {

    void normalize_vector_bridge(double* vec_in, double* vec_out);
} 

TEST(NormalizeVector, NormalCase) {
    double vec_in[3] = {1.0, 2.0, 3.0};
    double result[3] = {0.0, 0.0, 0.0};
    double expected_normalized[3]={0.2672612419124244, 0.5345224838248488, 0.8017837257372732};

    normalize_vector_bridge(vec_in, result);

    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR(result[i], expected_normalized[i], 1e-12) << "Mismatch at index " << i << "\n";
    }
}

TEST(NormalizeVector, InvalidInput) {
    double vec_in[3] = {6.0, 60.0, 600.0};
    double result[3] = {0.0, 0.0, 0.0};
    double expected_normalized[3]={0.0, 0.0, 0.0};

    normalize_vector_bridge(vec_in, result);

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], expected_normalized[i]) << "Mismatch at index " << i << "\n";
    }
}

