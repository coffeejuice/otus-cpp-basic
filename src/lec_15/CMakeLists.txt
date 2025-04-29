cmake_minimum_required(VERSION 3.3)

project(Lecture15StdGeneral)

add_executable(lec_15_01_string_file_ext lec_15_01_string_file_ext.cpp)
add_executable(lec_15_02_string_api      lec_15_02_string_api.cpp)
add_executable(lec_15_03_string_modify   lec_15_03_string_modify.cpp)
add_executable(lec_15_04_numeric_limits  lec_15_04_numeric_limits.cpp)
add_executable(lec_15_05_filesystem      lec_15_05_filesystem.cpp)
add_executable(lec_15_06_chrono          lec_15_06_chrono.cpp)
add_executable(lec_15_07_streams         lec_15_07_streams.cpp)
add_executable(regex                     regex.cpp)


set_target_properties(
    lec_15_01_string_file_ext 
    lec_15_02_string_api
    lec_15_03_string_modify
    lec_15_04_numeric_limits
    lec_15_05_filesystem
    lec_15_06_chrono
    lec_15_07_streams
    regex
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)