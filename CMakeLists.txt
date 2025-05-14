cmake_minimum_required(VERSION 3.10)
project(condition_variable)

find_package(Threads REQUIRED)

add_executable(1.condition.intro 1.condition.intro.cpp)
add_executable(2.condition.solution 2.condition.solution.cpp)
add_executable(3.waiting_queue 3.waiting_queue.cpp)