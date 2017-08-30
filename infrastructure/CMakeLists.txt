project(infrastucture)

set(HEADER_FILES
        types.hpp
        inout.hpp)

set(SOURCE_FILES
        inout.cpp
        set.cpp)

add_library(infrastructure STATIC ${SOURCE_FILES} ${HEADER_FILES})
