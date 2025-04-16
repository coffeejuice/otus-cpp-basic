#pragma once

#include "person.h"

class Student : public Person {
public:
	Student(
		const std::string &first_name,
		const std::string &second_name,
		const std::string &third_name,
		const std::string &group)
			: Person{first_name, second_name, third_name},
		  m_group{group} {}

	std::string group() const { return m_group; }

private:
	std::string m_group;
};

std::ostream &operator<<(std::ostream &os, const Student &student) {
	// Call the operactor<< for the base part of the Student object (Person)
	os << static_cast<const Person &>(student);
	// And then print the rest part - group field
	os << " Group: " << student.group();
	return os;
}