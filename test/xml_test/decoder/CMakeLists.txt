set(SOURCES run_test.cpp
            uint_fixture.cpp     
            int_fixture.cpp     
            float_fixture.cpp
    )


add_executable(decoder_test ${SOURCES})
target_link_libraries(decoder_test pniio ${CPPUNIT_LIBRARIES})
add_test(NAME "XML::decoders"
         COMMAND decoder_test)
