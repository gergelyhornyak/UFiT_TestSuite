subroutine find_index_bridge(grid, sz, target_loc, idx_in, idx_out) bind(C, name="find_index_bridge")

  !Index of gridpoint below ; grid is increasing
  use iso_c_binding

  use UFiT_Functions_Fortran, only : find_index 

  integer(c_int), intent(in)  :: sz
  integer(c_int), intent(in)  :: idx_in
  real(c_double), intent(in)  :: target_loc
  real(c_double), intent(in)  :: grid(sz)

  integer(c_int), intent(out) :: idx_out

  idx_out = find_index(grid, sz, target_loc, idx_in)

end subroutine find_index_bridge
