#
# regression tests
#

set(ISSUE32_SRC issue_32.cpp)
set_boost_test_definitions(ISSUE32_SRC "Regression test for issue 32")
add_executable(regression_issue_32 EXCLUDE_FROM_ALL ${ISSUE32_SRC})
target_link_libraries(regression_issue_32 pniio Boost::unit_test_framework)
add_boost_logging_test("regressions::issue_32" 
                       regression_issue_32
                       ${CMAKE_CURRENT_BINARY_DIR})
                       
add_dependencies(check regression_issue_32)