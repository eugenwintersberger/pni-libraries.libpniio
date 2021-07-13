set(HEADER_FILES 
add_op.hpp
div_op.hpp
inplace_arithmetics.hpp
mult_op.hpp
op_traits.hpp
sub_op.hpp
)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/algorithms/math)

