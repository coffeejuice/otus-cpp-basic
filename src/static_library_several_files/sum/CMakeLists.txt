cmake_minimum_required(VERSION 3.5)

project(17.static_library)

add_library(sumLib STATIC 
	sum_int.cpp
	sum_int.h
	sum_double.cpp
	sum_double.h
)


