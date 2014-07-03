set(SOURCES check_type_test.cpp
            utils_test.cpp
           )

add_executable(utils_test ${SOURCES})
target_link_libraries(utils_test pniio ${CPPUNIT_LIBRARIES})
add_test(utils_test utils_test)
