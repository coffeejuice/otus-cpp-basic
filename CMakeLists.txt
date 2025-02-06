cmake_minimum_required(VERSION 3.12)

project(guess_project LANGUAGES CXX)

add_executable(guess_project
	guess_the_number.cpp
	guess_funcs.hpp
	guess_funcs.cpp
)

target_compile_features(guess_project PUBLIC cxx_std_17)
target_compile_options(guess_project PUBLIC /W4 /WX)