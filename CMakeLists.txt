cmake_minimum_required(VERSION 3.12)

project(guess_project LANGUAGES CXX)

add_executable(tests main.cpp)
target_link_libraries(tests gtest gtest_main)
add_subdirectory(googletest)

target_compile_features(tests PUBLIC cxx_std_17)

# Set compiler warning flags based on compiler identification
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Microsoft Visual C++ compiler
    target_compile_options(tests PUBLIC /W4 /WX)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC compiler
    target_compile_options(tests PUBLIC -Wall -Wextra -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    # Clang compiler (including Apple's version)
    target_compile_options(tests PUBLIC -Wall -Wextra -pedantic)
else()
    # Default case for other compilers
    message(WARNING "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}. No specific warning flags set.")
endif()