cmake_minimum_required(VERSION 3.15)

project(20.move_n_noexcept)

add_executable(rvo rvo.cpp)
add_executable(move move.cpp)
add_executable(universal_references universal_references.cpp)
add_executable(gcd gcd.cpp)
add_executable(gcd_exceptions gcd_exceptions.cpp)
add_executable(noexcept noexcept.cpp)
add_executable(previous previous.cpp)

set_target_properties(
  noexcept rvo move universal_references gcd gcd_exceptions previous
  PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
