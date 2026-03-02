#include "testSuiteHeader.hpp"

/* 78 subroutine
ORDER:
initialize_variables,
parse_command_args
parse_command_file
load_input
load_Bfield
process_Bfield
get_available_resource
run_trace
write_output
cleanup
*/

int str_mx = 300;

extern "C" {

    //float __ufit_functions_fortran_MOD_vecdot(float *vec1, float *vec2);
    extern int __ufit_functions_fortran_MOD_geometry;
    extern int __ufit_functions_fortran_MOD_bfile_type;
    extern int __ufit_functions_fortran_MOD_input_type;

    extern bool __ufit_functions_fortran_MOD_grid_regular;
    extern bool __ufit_functions_fortran_MOD_grid_separate;
    extern bool __ufit_functions_fortran_MOD_periodic_x;
    extern bool __ufit_functions_fortran_MOD_periodic_y;
    extern bool __ufit_functions_fortran_MOD_periodic_z;
    extern bool __ufit_functions_fortran_MOD_periodic_phi;

    extern bool __ufit_functions_fortran_MOD_print_devices;
    extern bool __ufit_functions_fortran_MOD_save_endpoints;
    extern bool __ufit_functions_fortran_MOD_save_q;
    extern bool __ufit_functions_fortran_MOD_save_fieldlines;
    extern bool __ufit_functions_fortran_MOD_save_connections;
    extern bool __ufit_functions_fortran_MOD_user_defined;
    extern bool __ufit_functions_fortran_MOD_check_starts;
    extern bool __ufit_functions_fortran_MOD_normalised_B;
    extern bool __ufit_functions_fortran_MOD_include_curvature;

    extern int __ufit_functions_fortran_MOD_num_proc;
    extern int __ufit_functions_fortran_MOD_max_steps;
    extern int __ufit_functions_fortran_MOD_integration_scheme;
    extern double __ufit_functions_fortran_MOD_step_size;

    extern char __ufit_functions_fortran_MOD_cmd_filename[str_mx];
    extern char __ufit_functions_fortran_MOD_B_filename[str_mx];
    extern char __ufit_functions_fortran_MOD_in_filename[str_mx];
    extern char __ufit_functions_fortran_MOD_out_filename[str_mx];

    void __ufit_functions_fortran_MOD_initialize_variables();
} 

void setFortranString(char* fortranArray, size_t arrSize, const std::string& cppString) {
    std::memset(fortranArray, ' ', arrSize);
    size_t copyLen = std::min(cppString.length(), arrSize);
    std::memcpy(fortranArray, cppString.data(), copyLen);
    fortranArray[arrSize-1] = '\0'; // Ensure null termination
}

void setVariables() {
    __ufit_functions_fortran_MOD_geometry = 0;
    __ufit_functions_fortran_MOD_bfile_type = -1;
    __ufit_functions_fortran_MOD_input_type = 0;
    __ufit_functions_fortran_MOD_grid_regular = true;
    __ufit_functions_fortran_MOD_grid_separate = false;
    __ufit_functions_fortran_MOD_periodic_x = false;
    __ufit_functions_fortran_MOD_periodic_y = false;
    __ufit_functions_fortran_MOD_periodic_z = false;
    __ufit_functions_fortran_MOD_periodic_phi = false;
    __ufit_functions_fortran_MOD_print_devices = false;
    __ufit_functions_fortran_MOD_save_endpoints = false;
    __ufit_functions_fortran_MOD_save_q = false;
    __ufit_functions_fortran_MOD_save_fieldlines = false;
    __ufit_functions_fortran_MOD_save_connections = false;
    __ufit_functions_fortran_MOD_user_defined = false;
    __ufit_functions_fortran_MOD_check_starts = false; 
    __ufit_functions_fortran_MOD_normalised_B = false;
    __ufit_functions_fortran_MOD_include_curvature = false;
    __ufit_functions_fortran_MOD_num_proc = 1;
    __ufit_functions_fortran_MOD_max_steps = 5000;
    __ufit_functions_fortran_MOD_integration_scheme = 1;
    __ufit_functions_fortran_MOD_step_size = 0.005;
    setFortranString(__ufit_functions_fortran_MOD_cmd_filename,str_mx,"ufit.dat");
    setFortranString(__ufit_functions_fortran_MOD_B_filename,str_mx,"ufit.bin");
    setFortranString(__ufit_functions_fortran_MOD_in_filename,str_mx,"ufit.inp");
    setFortranString(__ufit_functions_fortran_MOD_out_filename,str_mx,"ufit.flf");
}

TEST(TestUFiTFunction, TestInitializeVariables) {
    __ufit_functions_fortran_MOD_initialize_variables();
    EXPECT_EQ(__ufit_functions_fortran_MOD_geometry, 0) << "Geometry should be initialized to 0, but got: " << __ufit_functions_fortran_MOD_geometry << "\n";
    EXPECT_EQ(__ufit_functions_fortran_MOD_bfile_type, -1);
    EXPECT_EQ(__ufit_functions_fortran_MOD_input_type, 0);
    EXPECT_TRUE(__ufit_functions_fortran_MOD_grid_regular);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_grid_separate);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_periodic_x) << "Periodic X should be initialized to false, but got: " << __ufit_functions_fortran_MOD_periodic_x << "\n";
    EXPECT_FALSE(__ufit_functions_fortran_MOD_periodic_y);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_periodic_z);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_periodic_phi);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_print_devices);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_save_endpoints);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_save_q);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_save_fieldlines);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_save_connections);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_user_defined);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_check_starts);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_normalised_B);
    EXPECT_FALSE(__ufit_functions_fortran_MOD_include_curvature);
    EXPECT_EQ(__ufit_functions_fortran_MOD_num_proc, 1);
    EXPECT_EQ(__ufit_functions_fortran_MOD_max_steps, 5000) << "Max steps should be initialized to 5000, but got: " << __ufit_functions_fortran_MOD_max_steps << "\n";
    EXPECT_EQ(__ufit_functions_fortran_MOD_integration_scheme, 1);
    EXPECT_FLOAT_EQ(__ufit_functions_fortran_MOD_step_size, 0.005);
    EXPECT_STREQ(__ufit_functions_fortran_MOD_cmd_filename, "ufit.dat") << "Command filename should be initialized to 'ufit.dat', but got: " << __ufit_functions_fortran_MOD_cmd_filename << "\n";
    EXPECT_STREQ(__ufit_functions_fortran_MOD_B_filename, "ufit.bin");
    EXPECT_STREQ(__ufit_functions_fortran_MOD_in_filename, "ufit.inp");
    EXPECT_STREQ(__ufit_functions_fortran_MOD_out_filename, "ufit.flf");
    return 0;
}