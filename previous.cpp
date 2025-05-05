#include <iostream>

namespace basics {

	void func_with_throw() {
		std::cout << "func_with_throw - before throw" << std::endl;

		throw 42; // 43, 98 // int

		std::cout << "func_with_throw - after throw" << std::endl;
	}

	void calling_function() {
		std::cout << "calling_function - before call" << std::endl;

		func_with_throw();

		std::cout << "calling_function - after call" << std::endl;
	}

	void example() {
		try {

			std::cout << "example - before call" << std::endl;

			calling_function();

			std::cout << "example - after call" << std::endl;


		} catch(float f) {
			std::cout << "example - float catch with f = " << f << std::endl;
			
		} catch(int i) {
			std::cout << "example - int catch with i = " << i << std::endl;
		} catch(...) {
			std::cout << "example - ... catch" << std::endl;
		}

	}

}

namespace structs {

	struct IException {
		virtual const char* what() const = 0;
	};

	struct LogicErrorException : IException {
		LogicErrorException(const std::string& msg) : m_msg{msg} {}

		const char* what() const override {
			return m_msg.data();
		}
	private:
		std::string m_msg;
	};

	struct ExecutionException : IException {
		ExecutionException(const std::string& msg) : m_msg{msg} {}

		const char* what() const override {
			return m_msg.data();
		}

		void* context() const {
			return nullptr;/// ....
		}
	private:
		std::string m_msg;
	};

	void example() {

		try {

			throw LogicErrorException{"division by zero!"};

		} catch(const ExecutionException& ex) {
			ex.context(); // ...
		} catch(const LogicErrorException ex) {
			ex.what(); // ...
		} catch(const IException& ex) {
			ex.what();
		}

	}

}

int main() {

	basics::example();
	structs::example();

}