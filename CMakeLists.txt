cmake_minimum_required(VERSION 3.12)

project(09.Polymorphism)

add_subdirectory(inheritance)

add_executable(animal animal.cpp)
set_target_properties(animal PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(details details.cpp)
set_target_properties(details PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(complex_class_1 complex_class_1.cpp)
set_target_properties(complex_class_1 PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(complex_class_2 complex_class_2.cpp)
set_target_properties(complex_class_2 PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(complex_class_3 complex_class_3.cpp)
set_target_properties(complex_class_3 PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(complex_naive complex_naive.cpp)
set_target_properties(complex_naive PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(complex_struct complex_struct.cpp)
set_target_properties(complex_struct PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(shapes_1 shapes_1.cpp)
set_target_properties(shapes_1 PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(shapes_virtual shapes_virtual.cpp)
set_target_properties(shapes_virtual PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

add_executable(pure_virtual_call pure_virtual_call.cpp)
set_target_properties(pure_virtual_call PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)
