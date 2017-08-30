include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicSomTests
        test.cpp)
add_definitions(/EHsc)

target_link_libraries(runBasicSomTests gtest gtest_main)
target_link_libraries(runBasicSomTests som infrastructure)
