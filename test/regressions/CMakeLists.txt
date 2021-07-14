#
# regression tests
#

set(ISSUE32_SRC issue_32.cpp)
set_boost_test_definitions(ISSUE32_SRC "Regression test for issue 32")
add_executable(regression_issue_32 EXCLUDE_FROM_ALL ${ISSUE32_SRC})
target_link_libraries(regression_issue_32 pninexus Boost::unit_test_framework)
add_boost_logging_test("regressions::issue_32" 
                       regression_issue_32
                       ${CMAKE_CURRENT_BINARY_DIR})
                       
set(ISSUE33_SRC issue_33.cpp)
set_boost_test_definitions(ISSUE33_SRC "Regression test for issue 33")
add_executable(regression_issue_33 EXCLUDE_FROM_ALL ${ISSUE33_SRC})
target_link_libraries(regression_issue_33 pninexus Boost::unit_test_framework)
add_boost_logging_test("regressions::issue_33" 
                       regression_issue_33
                       ${CMAKE_CURRENT_BINARY_DIR})   
                      
configure_file(eiger_master_stripped.h5 eiger_master_stripped.h5 COPYONLY)                      
set(ISSUE37_SRC issue_37.cpp)
set_boost_test_definitions(ISSUE37_SRC "Regression test for issue 37")
add_executable(regression_issue_37 EXCLUDE_FROM_ALL ${ISSUE37_SRC})
target_link_libraries(regression_issue_37 pninexus Boost::unit_test_framework)
add_boost_logging_test("regressions::issue_37" 
                       regression_issue_37
                       ${CMAKE_CURRENT_BINARY_DIR})
                       
add_dependencies(check regression_issue_32 
                       regression_issue_33 
                       regression_issue_37)