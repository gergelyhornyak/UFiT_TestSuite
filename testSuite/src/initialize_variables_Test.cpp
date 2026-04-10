#include "testSuiteHeader.hpp"

extern "C" {

    extern int __ufit_definitions_fortran_MOD_geometry;
    extern int __ufit_definitions_fortran_MOD_bfile_type;
    extern int __ufit_definitions_fortran_MOD_input_type;

    extern bool __ufit_definitions_fortran_MOD_grid_regular;
    extern bool __ufit_definitions_fortran_MOD_grid_separate;
    extern bool __ufit_definitions_fortran_MOD_periodic_x;
    extern bool __ufit_definitions_fortran_MOD_periodic_y;
    extern bool __ufit_definitions_fortran_MOD_periodic_z;
    extern bool __ufit_definitions_fortran_MOD_periodic_phi;

    extern bool __ufit_definitions_fortran_MOD_print_devices;
    extern bool __ufit_definitions_fortran_MOD_save_endpoints;
    extern bool __ufit_definitions_fortran_MOD_save_q;
    extern bool __ufit_definitions_fortran_MOD_save_fieldlines;
    extern bool __ufit_definitions_fortran_MOD_save_connection;
    extern bool __ufit_definitions_fortran_MOD_user_defined;
    extern bool __ufit_definitions_fortran_MOD_check_starts;
    extern bool __ufit_definitions_fortran_MOD_normalized_b;
    extern bool __ufit_definitions_fortran_MOD_include_curvature;

    extern int __ufit_definitions_fortran_MOD_num_proc;
    extern int __ufit_definitions_fortran_MOD_max_steps;
    extern int __ufit_definitions_fortran_MOD_integration_scheme;
    extern double __ufit_definitions_fortran_MOD_step_size;

    extern char __ufit_definitions_fortran_MOD_cmd_filename[300];
    extern char __ufit_definitions_fortran_MOD_b_filename[300];
    extern char __ufit_definitions_fortran_MOD_in_filename[300];
    extern char __ufit_definitions_fortran_MOD_out_filename[300];

    void __ufit_functions_fortran_MOD_initialize_variables();
} 

std::string getFortranString(const char* fortranString, size_t maxLen) {
    // 1. Read the exact number of characters (ignoring null terminators)
    std::string s(fortranString, maxLen);
    
    // 2. Trim all trailing spaces
    size_t endPos = s.find_last_not_of(' ');
    if (std::string::npos != endPos) {
        s = s.substr(0, endPos + 1);
    } else {
        s = ""; // String is entirely spaces
    }
    
    return s;
}

TEST(InitializeVariables, CorrectInit) {
    __ufit_functions_fortran_MOD_initialize_variables();
    EXPECT_EQ(__ufit_definitions_fortran_MOD_geometry, 0) << "Geometry should be initialized to 0, but got: " << __ufit_definitions_fortran_MOD_geometry << "\n";
    EXPECT_EQ(__ufit_definitions_fortran_MOD_bfile_type, -1);
    EXPECT_EQ(__ufit_definitions_fortran_MOD_input_type, 0);
    EXPECT_TRUE(__ufit_definitions_fortran_MOD_grid_regular);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_grid_separate);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_periodic_x) << "Periodic X should be initialized to false, but got: " << __ufit_definitions_fortran_MOD_periodic_x << "\n";
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_periodic_y);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_periodic_z);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_periodic_phi);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_print_devices);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_save_endpoints);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_save_q);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_save_fieldlines);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_save_connection);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_user_defined);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_check_starts);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_normalized_b);
    EXPECT_FALSE(__ufit_definitions_fortran_MOD_include_curvature);
    EXPECT_EQ(__ufit_definitions_fortran_MOD_num_proc, 1);
    EXPECT_EQ(__ufit_definitions_fortran_MOD_max_steps, 5000) << "Max steps should be initialized to 5000, but got: " << __ufit_definitions_fortran_MOD_max_steps << "\n";
    EXPECT_EQ(__ufit_definitions_fortran_MOD_integration_scheme, 1);
    EXPECT_FLOAT_EQ(__ufit_definitions_fortran_MOD_step_size, 0.005);
    EXPECT_EQ(getFortranString(__ufit_definitions_fortran_MOD_cmd_filename, sizeof(__ufit_definitions_fortran_MOD_cmd_filename)), "ufit.dat") << "Command filename should be initialized to 'ufit.dat', but got: " << __ufit_definitions_fortran_MOD_cmd_filename << "\n";
    EXPECT_EQ(getFortranString(__ufit_definitions_fortran_MOD_b_filename, sizeof(__ufit_definitions_fortran_MOD_b_filename)), "ufit.bin");
    EXPECT_EQ(getFortranString(__ufit_definitions_fortran_MOD_in_filename, sizeof(__ufit_definitions_fortran_MOD_in_filename)), "ufit.inp");
    EXPECT_EQ(getFortranString(__ufit_definitions_fortran_MOD_out_filename, sizeof(__ufit_definitions_fortran_MOD_out_filename)), "ufit.flf");
}