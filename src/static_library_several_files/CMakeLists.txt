cmake_minimum_required(VERSION 3.5)

project(17.static_library_several_files)

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


