#include "tracer.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace motivation_0 {

	struct Employee {

		// Employee() {} 
		// Employee(const Employee& ) {}
		// Employee(Employee&&) {}

		// Employee& operator=(const Employee& ) {}
		// Employee& operator=(Employee&& ) {}

		int age;

		std::string first;
		std::string middle;
		std::string last;
	};

	void i_want_to_move_example() {

		std::vector<Employee> empls;
		// empls.push_back( {...} )

		std::cout << "Enter the next employee, please: " << std::endl;
		for (int i = 0; i < 10; ++i) {
			Employee empl;
			std::cin >> empl.age;	 // 42
			std::cin >> empl.first;	 // Ivan
			std::cin >> empl.middle; // Sergeevich
			std::cin >> empl.last;	 // Petrov

			empls.push_back( std::move(empl) );
			// .......

			// std::cout << "You've entered: " << empl.age << ' ' << empl.first << ' ' << empl.middle << ' ' << empl.last << std::endl;
			// You've entered: 42 Ivan Sergeevich Petrov
		}
	}

	struct StringWithMoving {
		StringWithMoving() : m_data{nullptr}, m_size{0} {}

		StringWithMoving(const char *str) : StringWithMoving{} {
			if (!str)
				return;

			m_size = std::strlen(str);
			m_data = new char[m_size + 1];
			std::copy(str, str + m_size, m_data);
			m_data[m_size + 1] = '\0';
		}

		StringWithMoving(const StringWithMoving& rhs) : StringWithMoving{rhs.get()} {}

		~StringWithMoving() {
			delete [] m_data;
		}

		void move_from(StringWithMoving& rhs) {
			// delete [] m_data;
			char* tmp = m_data;
			size_t tmp_size = m_size;

			m_data = rhs.m_data;
			m_size = rhs.m_size;

			rhs.m_data = tmp;
			rhs.m_size = m_size;
		}

		const char* get() const {
			if(m_size)
				return m_data;
			else
				return "";
		}

	private:
		char *m_data;
		size_t m_size;
	};


	struct Employee_with_moving {
		void move_from(Employee_with_moving& rhs) {
			age = rhs.age;

			first.move_from(rhs.first);
			middle.move_from(rhs.middle);
			last.move_from(rhs.last);
		}

		int age;

		StringWithMoving first;
		StringWithMoving middle;
		StringWithMoving last;
	};

	// 1. move - воровство данных у rhs
	// 2. rhs после воровства всё ещё живёт
	// 3. для простых типов перемещение смысла не имеет

	void now_i_can_move_example() {

		std::vector<Employee_with_moving> empls;

		std::cout << "Enter the next employee, please: " << std::endl;
		for (int i = 0; i < 10; ++i) {
			empls.push_back(Employee_with_moving{});

			Employee_with_moving empl;
			empl.age;	 // 42
			empl.first;	 // Ivan
			empl.middle; // Sergeevich
			empl.last;	 // Petrov

			empls.back().move_from(empl);

			// std::cout << "You've entered: " << empl.age << ' ' << empl.first << ' ' << empl.middle << ' ' << empl.last << std::endl;
			// You've entered: 0    
		}
	}

}

namespace motivation_1 {

	void example1() {

		std::vector<std::string> strings1{
			"first",
			"second",
			"third"};

		// some code here

		std::vector<std::string> strings2;

		// now we need to take the first string from the string1 vector
		// and put it into the strings2 vector

		// without moving
		{
			std::string temp = strings1.back(); // first copy here
			strings1.pop_back();

			strings2.push_back(temp); // second copy here

			// we still can use temp here with correct behaviour
			std::cout << temp;
		}

		// with moving
		{
			int v1 = 42;
			int v2 = v1;

			std::string temp = std::move(strings1.back()); // no copy, but moving
			strings1.pop_back();

			strings2.emplace_back(std::move(temp)); // no copy, but moving

			// we can't use a value of the temp here (undefined)
			temp = "value";
		}
	}

	void example2() {

		struct Employee {
			std::string first;
			std::string middle;
			std::string last;
		};

		std::vector<Employee> empls;
		for (int i = 0; i < 3; ++i) {
			Employee empl;
			std::cin >> empl.first;
			std::cin >> empl.middle;
			std::cin >> empl.last;

			empls.emplace_back(std::move(empl));
		}
	}

}

namespace custom {

	struct string {
		string() : m_data{nullptr}, m_size{0} {}

		explicit string(const char *value) {
			m_size = std::strlen(value) + 1; // one more byte for term null
			if (m_size) {
				m_data = new char[m_size];
				std::copy(value, value + m_size, m_data);
				m_data[m_size - 1] = '\0';
			}
		}

		// copy ctor
		string(const string &rhs) {
			m_size = rhs.m_size;
			m_data = new char[m_size];
			std::copy(rhs.m_data, rhs.m_data + m_size, m_data);
		}

		// l-value reference - T&, string& 
		// r-value reference - T&&, string&& 

		// move ctor
		string(string &&rhs)
			: m_data{nullptr}, m_size{0} {
			swap(*this, rhs);
		}

		~string() {
			delete[] m_data;
		}

		// void test(int) {}
		// void test(float) {}
		// void test(std::string) {}

		void test() {

			std::string str{"Some"};

			// 1. copy ctor
			std::string copy{ str }; // std::string&
			// move ctor
			std::string move{ std::move(str) }; // std::string& -> std::string&&

			// 2. copy assignment operator
			copy = str;

			// move assignment operator
			copy = std::move(str);
		}

		string& operator=(const string& rhs) {

		}

		string& operator=(string&& rhs) {

		}

		const char *get() const {
			if (m_size)
				return m_data;
			else
				return "\0";
		}

	private:
		friend void swap(string &lhs, string &rhs) {
			std::swap(lhs.m_data, rhs.m_data);
			std::swap(lhs.m_size, rhs.m_size);
		}

		char *m_data;
		size_t m_size;
	};

	void example() {
		std::cout << std::endl
				  << std::endl;
		std::cout << "*****     custom::example()     *****" << std::endl;

		custom::string str{"trololo"};
		std::cout << str.get() << std::endl;

		std::cout << "***   after copy:" << std::endl;
		custom::string str2{str}; // copy or move? -> copy

		std::cout << "str2 = " << str2.get() << std::endl;
		std::cout << "str = " << str.get() << std::endl;

		std::cout << "***   after move:" << std::endl;
		custom::string str3{std::move(str)};

		std::cout << "str3 = " << str2.get() << std::endl;
		std::cout << "str = " << str.get() << std::endl;

		std::cout << std::endl
				  << std::endl;
	} // destructor for str

}

// Move medium
void moveMedium() {
	std::cout << "Move medium:" << std::endl;

	std::string value{"Aha-a-a-a-a-a!"};

	std::string value2 = std::move(value);

	std::cout << "  value is: \"" << value << "\" at #" << &value << std::endl; // NOLINT

	//                                                   the comment disables linter ^^^^^^
	//                                                   warning about variable usage
	//                                                   after moving

	std::cout << "  value2 is: \"" << value2 << "\" at #" << &value2 << std::endl;
}

#if 0
// Possible implementation of std::move
template <typename T>
typename std::remove_reference<T>::type && move(T &&arg) {
    // Move doesn't move!

    return static_cast<typename std::remove_reference<T>::type &&>(arg);
}
#endif

void handleBigObjectFunc(const std::string &bigObject) {
	// just a reference here - it is not an "temporary" or "moved" object

	std::cout << "    handleBigObjectFunc(std::string &) <-- reference" << std::endl;
	std::cout << "       object value: \"" << bigObject << "\"" << std::endl;
	std::cout << "       object address: #" << &bigObject << std::endl;
}

void handleBigObjectFunc(std::string &&bigObject) {
	// r-value reference here - it is a "temporary" or "moved" object
	// r-value - "right" (r) in the name because all it can do is stand on the right

	std::cout << "    handleBigObjectFunc(std::string &&) <-- r-value" << std::endl;
	std::cout << "       object value: \"" << bigObject << "\"" << std::endl;
	std::cout << "       object address: #" << &bigObject << std::endl;

	auto local = std::move(bigObject);
	local += "more and more";
}

Tracer makeNrvoMediumTracer(const char *name, const int foo) {
	if (foo % 2 == 0) {
		Tracer result1{name};

		return result1;
	}

	Tracer result2{"other"};

	return result2;
}

void test(const int) {
	std::cout << "Start of the main" << std::endl;

	moveMedium();

	{
		std::cout << "Overload:" << std::endl;
		// Move basic
		std::string bigString{"very very big string"}; // 10 GB!

		handleBigObjectFunc(bigString);
		handleBigObjectFunc(std::move(bigString));

		std::cout << "    Repeating!" << std::endl;
		handleBigObjectFunc(bigString); // NOLINT
		handleBigObjectFunc(std::move(bigString));

		std::cout << "  \"True\" r-value:" << std::endl;
		handleBigObjectFunc("\"true\" r-value content");
	}

	{
		std::cout << "Big:" << std::endl;

		Tracer bigTracer{"bigTracer1"};	   // 10 GB again here!
		Tracer otherTracer{"otherTracer"}; // Small object

		otherTracer = bigTracer; // Already 20 GB here!

		otherTracer = std::move(bigTracer); // maybe only 10 GB here

		int foo = 42;
		const Tracer moveTracer = makeNrvoMediumTracer("moveTracer", foo);
	}

	std::cout << "In vector:" << std::endl;

	std::vector<Tracer> vector;
	Tracer tracer4{"4 (push_back + std::move)"};
	Tracer tracer5{"4 (push_back + std::move)"};

	vector.emplace_back("1 (emplace_back)");
	vector.emplace_back("2 (emplace_back)");

	vector.push_back(Tracer("3 (push back)")); // NOLINT
	vector.push_back(std::move(tracer4));
	vector.push_back(std::move(tracer5));

	std::cout << "End of the main" << std::endl;
}

//-----------------------------------------------------------------------------

int main(const int argc, char *[]) {
	try {
		test(argc);
	} catch (...) {
		std::cout << "Unexpected error" << std::endl;

		return 1;
	}

	return 0;
}