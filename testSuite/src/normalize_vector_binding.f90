subroutine normalize_vector_bridge(vec_in, vec_out) bind(C, name="normalize_vector_bridge")
    use iso_c_binding
    
    use UFiT_Functions_Fortran, only : normalize_vector 
    
    real(c_double), intent(in)  :: vec_in(3)
    real(c_double), intent(out) :: vec_out(3)
    
    vec_out = normalize_vector(vec_in)
end subroutine normalize_vector_bridge