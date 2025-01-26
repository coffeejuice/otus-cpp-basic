cmake_minimum_required(VERSION 3.12)

project(hello_world_project CXX)

add_executable(hello_world 
hello_world.cpp 
example.cpp 
example.h 
move_me_out.cpp 
move_me_out.h
)

# set_target_properties(hello_world PROPERTIES
#  CXX_STANDARD 17 
#  CXX_STANDARD_REQUIRED ON 
# )


# Compiler: Microsoft Visual Studio Build Tools compiler
# OS:       Windows 11
# IDE:      VSCode
target_compile_features(hello_world PUBLIC cxx_std_17)
target_compile_options(hello_world PUBLIC /W4 /WX)
