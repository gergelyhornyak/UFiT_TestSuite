subroutine find_index_irregular_bridge(target_loc,idx_in,idx_out) bind(C, name="find_index_irregular_bridge")

  !Index of gridpoint below ; grid is increasing
  use iso_c_binding

  use UFiT_Functions_Fortran, only : find_index_irregular
  
  implicit none

  integer(c_int), intent(in) :: idx_in
  real(c_double), intent(in) :: target_loc(3)

  integer(c_int), intent(out) :: idx_out

  idx_out = find_index_irregular(target_loc,idx_in)

end subroutine find_index_irregular_bridge
