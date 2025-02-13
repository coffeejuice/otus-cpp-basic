cmake_minimum_required(VERSION 3.30)
project(sea_battle CXX)
set(CMAKE_CXX_STANDARD 20)
add_executable(sea_battle main.cpp
    Menu.cpp
    Menu.hpp
    Field.cpp
    Field.hpp
    GameLogic.cpp
    GameLogic.hpp
    Action.cpp
    Action.hpp
    GameLoop.cpp
    GameLoop.hpp
    )
if (MSVC)
    target_compile_options(sea_battle PUBLIC /W4 /WX)
else()
    target_compile_options(sea_battle PUBLIC -Werror -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif()
