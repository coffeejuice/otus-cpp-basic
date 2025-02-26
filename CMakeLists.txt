cmake_minimum_required(VERSION 3.30)

# Using VERSION in 'project' will deifine varaibles:
# sea_batle_VERSION_MAJOR and sea_batle_VERSION_MINOR

project(sea_battle VERSION 1.0 LANGUAGES CXX)  

# Set C++ standard before 'add_executable' command

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set input header file 'main.h.in' for importing User Variables
# Variables, specified in header file will replace variables defined 
# in 'CMakeLists.txt', for example @sea_batle_VERSION_MAJOR@ and 
# @sea_batle_VERSION_MINOR@.

configure_file(mainConfig.h.in mainConfig.h)

add_executable(sea_battle main.cpp)

# Specify where the executable target should look for include files
target_include_directories(sea_battle PUBLIC "${PROJECT_BINARY_DIR}")

if (MSVC)
    target_compile_options(sea_battle PUBLIC /W4 /WX)
else()
    target_compile_options(sea_battle PUBLIC -Werror -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif()


