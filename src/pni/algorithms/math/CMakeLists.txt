set(HEADER_FILES 
${CMAKE_CURRENT_SOURCE_DIR}/add_op.hpp
${CMAKE_CURRENT_SOURCE_DIR}/div_op.hpp
${CMAKE_CURRENT_SOURCE_DIR}/inplace_arithmetics.hpp
${CMAKE_CURRENT_SOURCE_DIR}/mult_op.hpp
${CMAKE_CURRENT_SOURCE_DIR}/op_traits.hpp
${CMAKE_CURRENT_SOURCE_DIR}/sub_op.hpp
)

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pni/algorithms/math)

