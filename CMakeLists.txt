cmake_minimum_required(VERSION 3.30)

project(containers)

add_executable(containers main.cpp
        sequence_container.h
        single_linked_list_container.h
        double_linked_list_contaner.h)

set_target_properties(
        containers
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
