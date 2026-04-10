#include "testSuiteHeader.hpp"

/* 
    function find_index_irregular(target_loc,idx_in)
      !Index of gridpoint below ; grid is increasing
        INTEGER :: idx_in
        REAL(num) :: target_loc(3)
        INTEGER :: idx
        INTEGER :: find_index_irregular
        if ((target_loc(1) .ge. grid1_ir(1,idx_in)) .and. (target_loc(1) .lt. grid1_ir(2,idx_in)) &
           .and. (target_loc(2) .ge. grid2_ir(1,idx_in)) .and. (target_loc(2) .lt. &
           grid2_ir(2,idx_in)) .and. (target_loc(3) .ge. grid3_ir(1,idx_in)) .and. (target_loc(3) &
           .lt. grid3_ir(2,idx_in))) then
          find_index_irregular = idx_in
        else
          do idx=1,num_blocks
            if ((target_loc(1) .ge. grid1_ir(1,idx)) .and. (target_loc(1) .lt. &
                grid1_ir(2,idx)) .and. (target_loc(2) .ge. grid2_ir(1,idx)) .and. &
                (target_loc(2) .lt. grid2_ir(2,idx)) .and. (target_loc(3) .ge. &
                grid3_ir(1,idx)) .and. (target_loc(3) .lt. grid3_ir(2,idx))) then
              find_index_irregular = idx
              exit
            end if
          end do
        end if
    end function find_index_irregular
 */

extern "C" {
    // extern double __ufit_definitions_fortran_MOD_grid1_ir;
    // extern double __ufit_definitions_fortran_MOD_grid2_ir;
    // extern double __ufit_definitions_fortran_MOD_grid3_ir;
    // extern int __ufit_definitions_fortran_MOD_num_blocks;
    void setup_test_grids(int* n_blocks);
    void find_index_irregular_bridge(double* target_loc, int* idx_in, int* idx_out);
} 

TEST(FindIndexIrregular, MovesUpAndDown) {

    int n_blocks = 10;
    setup_test_grids(&n_blocks);
    
    double target_loc[3] = {5.5, 2.2, 1.1};
    int idx_in = 1;
    int idx_out = 0;
    int expected_idx_out = 5;

    find_index_irregular_bridge(target_loc, &idx_in, &idx_out);
    EXPECT_EQ(idx_out, expected_idx_out);

    target_loc[0] = 5.1;
    find_index_irregular_bridge(target_loc, &idx_in, &idx_out);
    EXPECT_EQ(idx_out, expected_idx_out);
}