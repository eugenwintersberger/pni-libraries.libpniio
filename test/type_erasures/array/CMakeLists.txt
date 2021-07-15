#need to define the version of the library
set(SOURCES
        array_creation_test.cpp
        array_access_test.cpp
        array_iterator_test.cpp
    )

if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

set_boost_test_definitions(SOURCES "testing the array type erasure")

add_executable(array_test EXCLUDE_FROM_ALL ${SOURCES} $<TARGET_OBJECTS:test_common>)
target_link_libraries(array_test pninexus Boost::unit_test_framework)
add_dependencies(check array_test)

add_boost_logging_test("type_erasure_test:array" array_test
                       ${PROJECT_BINARY_DIR}/test/type_erasures/array)
