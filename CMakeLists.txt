cmake_minimum_required(VERSION 3.30)

# Using VERSION in 'project' will deifine varaibles:
# sea_batle_VERSION_MAJOR and sea_batle_VERSION_MINOR

project(sea_battle VERSION 1.0.0 LANGUAGES CXX)  

# Set input header file 'main.h.in' for importing User Variables
# Variables, specified in header file will replace variables defined 
# in 'CMakeLists.txt', for example @sea_batle_VERSION_MAJOR@ and 
# @sea_batle_VERSION_MINOR@.

add_executable(sea_battle main.cpp)

# Example of a variable
set(VARIABLE "Trololo")

# Example of Message for Debuging
message("VARIABLE = ${VARIABLE}")
message("CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

configure_file( mainConfig.h.in 
                ${CMAKE_CURRENT_BINARY_DIR}/mainConfig.h
)

target_include_directories(
    sea_battle
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Set C++ standard before 'add_executable' command

# set(CMAKE_CXX_STANDARD 20) -- Deprecated
# set(CMAKE_CXX_STANDARD_REQUIRED True) - Deprecated

target_compile_features(sea_battle PUBLIC cxx_std_17)
set_target_properties(sea_battle PROPERTIES CXX_STANDARD_REQUIRED ON)


if (MSVC)
    target_compile_options(sea_battle PUBLIC /W4 /WX)
else()
    target_compile_options(sea_battle PUBLIC -Werror -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif()


