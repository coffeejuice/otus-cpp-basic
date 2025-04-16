#pragma once

#include <iostream>
#include <string>

// Слушатели курса
// Менторы
// Преподаватели
// Менеджеры

class Person {
public:
	Person() {}

	Person(
		const std::string &first_name,
		const std::string &middle_name,
		const std::string &last_name) : m_first_name{first_name},
										m_middle_name{middle_name},
										m_last_name{last_name} {
	}

	std::string first_name() const { return m_first_name; }
	std::string middle_name() const { return m_middle_name; }
	std::string last_name() const { return m_last_name; }

private:
	std::string m_first_name;
	std::string m_middle_name;
	std::string m_last_name;
};

std::ostream &operator<<(std::ostream &os, const Person &person) {
	os << person.first_name() << ' '
	   << person.middle_name() << ' '
	   << person.last_name();
	return os;
}
