subroutine setup_test_grids(n_blocks) bind(C, name="setup_test_grids")
    use iso_c_binding
    use UFiT_Definitions_Fortran, only : grid1_ir, grid2_ir, grid3_ir, num_blocks
    integer(c_int), intent(in) :: n_blocks

    num_blocks = n_blocks
    allocate(grid1_ir(2, n_blocks), grid2_ir(2, n_blocks), grid3_ir(2, n_blocks))
    
    ! Initialize with some dummy boundaries for testing
    grid1_ir(1, 5) = 5.0  ! Min X for block 5
    grid1_ir(2, 5) = 6.0  ! Max X for block 5
    grid2_ir(1, 5) = 2.0  ! Min Y
    grid2_ir(2, 5) = 3.0  ! Max Y
    grid3_ir(1, 5) = 1.0  ! Min Z
    grid3_ir(2, 5) = 2.0  ! Max Z
    
end subroutine setup_test_grids