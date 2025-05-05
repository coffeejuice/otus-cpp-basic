cmake_minimum_required(VERSION 3.24)

project(format)

find_package(fmt REQUIRED)

add_executable(${PROJECT_NAME} format.cpp)
target_link_libraries(${PROJECT_NAME} fmt::fmt)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
