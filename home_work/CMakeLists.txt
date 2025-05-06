cmake_minimum_required(VERSION 3.15)

project(20.move_n_noexcept)

add_executable(home_work home_work/home_work.cpp)

set_target_properties(home_work PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(
    home_work
  PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
