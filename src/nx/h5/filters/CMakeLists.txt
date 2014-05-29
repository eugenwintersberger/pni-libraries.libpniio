set(SOURCES lzf_c.c lzf_d.c lzf_filter.c)

add_library(filter_objects OBJECT ${SOURCES})
