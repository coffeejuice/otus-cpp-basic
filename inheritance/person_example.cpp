#include <iostream>
#include <string>

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

	std::string get_first_name() const { return m_first_name; }
	std::string get_middle_name() const { return m_middle_name; }
	std::string get_last_name() const { return m_last_name; }

private:
	std::string m_first_name;
	std::string m_middle_name;
	std::string m_last_name;
};

std::ostream &operator<<(std::ostream &os, const Person &person) {
	os << person.get_first_name() << ' '
	   << person.get_middle_name() << ' '
	   << person.get_last_name();
	return os;
}

int main() {

	Person person{
		"Ivan",
		"Ivanovich",
		"Ivanov"};

	std::cout << person << std::endl;

	return 0;
}