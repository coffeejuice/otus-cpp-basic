#include <iostream>
#include <string>
#include <vector>

struct Address {
	std::string city;
	std::string street;
	int building;
};

enum class Post {
	manager,
	developer,
	QA
};

struct Employee {
	std::string name;
	std::string surname;
	Address address;
	Post post;
};

struct Department {
	std::string name;
	std::vector<Employee> employees;
};

void example() {
	std::cout << "*** example ***" << std::endl;

	Address address;
	address.city = "Some city";
	address.street = "Some street";
	address.building = 42;

	Employee employee{
		"Name",
		"Surname",
		{
			"Some other city",
			"Some other street"
			// Does it work?
			// 40
		},
		Post::developer
	};

	Employee employee2;
	employee2.name = "Name";
	employee2.surname = "Surname";
	employee2.address.city = "Some other city";
	employee2.address.street = "Some other street";
	// employee2.address.building = 40
	employee2.post = Post::manager;

	Department department {
		"Super department!",
		{ // std::vector<Employee> starts here
			{ // The first Employee starts here
				"Name1",
				"Surname1",
				{
					"Some other city",
						"Some other street"
					// Does it work?
					// 40
				},
				Post::developer
			}, // The first Employee ends here
			{ // The second Employee starts here
				"Name2",
				"Surname2",
				{
					"Some other city",
						"Some other street"
					// Is is work?
					// 40
				},
				Post::QA
			} // The second Employee ends here
		} // std::vector<Employee> ends here
	}; // Department ends here
}

int main() {

	example();

	return 0;
}