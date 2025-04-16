cmake_minimum_required(VERSION 3.12)

add_executable(inheritance main.cpp person.h student.h)
set_target_properties(inheritance PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(person person_example.cpp person.h student.h)
set_target_properties(person PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)
