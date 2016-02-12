set(HEADER_FILES column_info.hpp
                 data_reader.hpp
                 deprecation_warning.hpp
                 image_channel_info.hpp
                 image_info.hpp
                 image_reader.hpp
                 spreadsheet_reader.hpp
                 strutils.hpp
                 exceptions.hpp
                 parsers.hpp
                 formatters.hpp
                 container_io_config.hpp
                 format.hpp
                 windows.hpp
                 )

install(FILES ${HEADER_FILES} 
        DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/pni/io)


add_subdirectory("cbf")
add_subdirectory("fio")
add_subdirectory("nx")
add_subdirectory("parsers")
add_subdirectory("formatters")
add_subdirectory("tiff")

