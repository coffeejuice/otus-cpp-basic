#include <iostream>

namespace defaults {

	class WithDefaultCtor {
	public:
		WithDefaultCtor() {}

		WithDefaultCtor(int value)
			: m_value{value} {}

		int get_value() const { return m_value; }

	private:
		int m_value;
	};

	class WithoutDefaultCtor {
	public:
		WithoutDefaultCtor(int value)
			: m_value{value} {}

		int get_value() const { return m_value; }

	private:
		int m_value;
	};

	void example() {
		std::cout << "*** defaults::example ***" << std::endl;

		WithDefaultCtor defaultConstructed{};
		std::cout << "defaultConstructed.get_value() = " << defaultConstructed.get_value() << std::endl;

		WithDefaultCtor argumentConstructed{42};
		std::cout << "argumentConstructed.get_value() = " << argumentConstructed.get_value() << std::endl;

		// Compile-time error here.
		// WithoutDefaultCtor defaultConstructed2{};

		// details.cpp: error: no matching function for call to 'defaults::WithoutDefaultCtor::WithoutDefaultCtor()'
		//       |   WithoutDefaultCtor defaultConstructed2;
		//       |                      ^~~~~~~~~~~~~~~~~~~
		// details.cpp note: candidate: 'defaults::WithoutDefaultCtor::WithoutDefaultCtor(int)'
		//       |   WithoutDefaultCtor(int value)
		//       |   ^~~~~~~~~~~~~~~~~~
		// details.cpp note:   candidate expects 1 argument, 0 provided
		// details.cpp note: candidate: 'constexpr defaults::WithoutDefaultCtor::WithoutDefaultCtor(const defaults::WithoutDefaultCtor&)'
		//       |  class WithoutDefaultCtor {
		//       |        ^~~~~~~~~~~~~~~~~~
		// details.cpp note:   candidate expects 1 argument, 0 provided

		WithDefaultCtor argumentConstructed2{56};
		std::cout << "argumentConstructed2.get_value() = " << argumentConstructed2.get_value() << std::endl;
	}

} // namespace defaults

namespace polymorphism {

	class Base {
	public:
		virtual int some_method(int arg1, float arg2) const {
			return 0;
		}
	};

	class Derived : public Base {
	public:
		// Ooops... It is not what we want!
		int some_method(int arg1, int arg2) const {
			return 1;
		}

		// Solution - override
		/*
		int some_method(int arg1, int arg2) const override {
		}
		*/
	};

} // polymorphism


int main() {
	int * a = new int{42};

	defaults::example();
	std::cout << std::endl;

	return 0;
}