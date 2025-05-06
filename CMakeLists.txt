cmake_minimum_required(VERSION 3.12)

project(test_project LANGUAGES CXX)

#download googletest sources at configure time to build directory
#build from sources at build time
include(FetchContent)
#describe how to get content
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        #it is advisable to use a hash for GIT_TAG rather than a branch or tag name.
        #A commit hash is more secure and helps to confirm that the downloaded contents are what you expected.
        GIT_TAG        6910c9d   # release-1.16.0
)
#make sure that all the dependencies are available
FetchContent_MakeAvailable(googletest)

#no add_subdirectory to googletest requires!

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Main target
add_executable(
        main
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

# Link test target against gtest libraries
target_link_libraries(
        test_list PRIVATE
        gtest
)

set_target_properties(main PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(test_list PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

find_package(Python3 COMPONENTS Interpreter Development)

set(Python3_EXECUTABLE /path/to/python3)
set(Python_EXECUTABLE /path/to/python)

# Set compiler warning flags based on compiler identification
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(main PRIVATE /W4 /WX)
    target_compile_options(test_list PRIVATE /W4 /WX)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(main PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(test_list PRIVATE -Wall -Wextra -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    target_compile_options(main PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(test_list PRIVATE -Wall -Wextra -pedantic)
else()
    message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}. No specific warning flags set.")
endif()
