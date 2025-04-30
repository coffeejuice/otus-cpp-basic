cmake_minimum_required(VERSION 3.5)

project(17.dynamic_library)

add_library(sumLib SHARED 
	sum.h
	sum.cpp
)

target_compile_definitions(sumLib
	PRIVATE
	-DBUILD_SUM_DLL
)
