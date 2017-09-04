project(infrastucture)

set(HEADER_FILES
        types.hpp
        help.h
        set.h
        setinfo.h
        feature.h
        inout.hpp)

set(SOURCE_FILES
        help.cpp
        inout.cpp
        setinfo.cpp
        feature.cpp
        set.cpp)

add_library(infrastructure STATIC ${SOURCE_FILES} ${HEADER_FILES})
