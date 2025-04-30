cmake_minimum_required(VERSION 3.5)

project(18.static_library)

add_subdirectory(sum)

add_executable(main
	main.cpp
)

target_link_libraries(main
	PRIVATE
	sumLib
)
target_include_directories(main
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/sum
)


