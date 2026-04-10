#include "testSuiteHeader.hpp"

/*
function find_index(grid,sz,target_loc,idx_in)
    !Index of gridpoint below ; grid is increasing
    INTEGER :: sz, idx_in
    REAL(num) :: target_loc
    REAL(num) :: grid(sz)
    INTEGER :: find_index
    find_index = idx_in
    if (grid(find_index) .le. target_loc) then
        do while ((find_index .lt. sz) .and. (grid(find_index+1) .le. target_loc))
        find_index = find_index + 1
        end do
    else
        do while ((find_index .gt. 1) .and. (grid(find_index) .gt. target_loc))
        find_index = find_index - 1
        end do
    end if
    find_index=MAX(MIN(find_index,sz-1),1)
end function find_index
*/

extern "C" {
    void find_index_bridge(double* grid, int* sz, double* target_loc, int* idx_in, int* idx_out);
} 

TEST(FindIndex, MovesUpAndDown) {
    double grid[5] = {0.0, 10.0, 20.0, 30.0, 40.0};
    int sz = 5;
    double target = 25.0;
    int out = 0;

    int guess_low = 1;
    find_index_bridge(grid, &sz, &target, &guess_low, &out);
    EXPECT_EQ(out, 3); // grid(3)=20, grid(4)=30. 25 is between them.

    int guess_high = 5;
    find_index_bridge(grid, &sz, &target, &guess_high, &out);
    EXPECT_EQ(out, 3); 
}
