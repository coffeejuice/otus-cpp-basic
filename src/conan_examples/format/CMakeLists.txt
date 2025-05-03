cmake_minimum_required(VERSION 3.12)

project(18.conan_example)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(format format.cpp)
set_target_properties(format 
	PROPERTIES CXX_STANDARD 17 
	CXX_STANDARD_REQUIRED ON
)

target_link_libraries(format 
	PRIVATE 
	${CONAN_LIBS}
)