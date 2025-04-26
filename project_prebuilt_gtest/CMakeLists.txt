cmake_minimum_required(VERSION 3.2)

project(GTestPrebuilt)

# Lookup for pre-built gtest
find_package(GTest)

# Main target
add_executable(
    demo
    src/main.cpp
    src/list.hpp
)

# Test target
add_executable(
    test_list
    test/test_list.cpp
)

# Add src to the include directories for the test target
target_include_directories(
    test_list PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

message(STATUS ${GTEST_INCLUDE_DIRS})
message(STATUS ${GTEST_LIBRARY})

# Add googletest to the include directories for the test target
target_include_directories(
    test_list PRIVATE
    ${GTEST_INCLUDE_DIRS}
)

# Link test target against gtest libraries
target_link_libraries(
    test_list PRIVATE
    ${GTEST_LIBRARY}
)

set_target_properties(demo PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(test_list PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

if (MSVC)
    target_compile_options(
        demo PRIVATE
        /W4
    )
    target_compile_options(
        test_list PRIVATE
        /W4
    )
else ()
    target_compile_options(
        demo PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(
        test_list PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()
