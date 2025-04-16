#include "student.h"

int main() {

	Student student{
		"Ivan",
		"Ivanivich",
		"Ivanov",
		"C++-basic-2022-03"};

	std::cout << student << std::endl;

	std::cout << student.first_name() << std::endl;
	std::cout << student.middle_name() << std::endl;
	std::cout << student.last_name() << std::endl;
	std::cout << student.group() << std::endl;

	return 0;
}