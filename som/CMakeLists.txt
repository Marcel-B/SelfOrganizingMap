project(som)

set(HEADER_FILES
        som.hpp)

set(SOURCE_FILES
        som.cpp)

add_library(som STATIC ${SOURCE_FILES} ${HEADER_FILES})
