#include <iostream>

enum class ErrorCode {
	Ok,
	Failed,
	NotFound,
	OutOfMemory
};

class Error {
public:
	Error() : m_code{ErrorCode::Ok} {}

	explicit Error(ErrorCode code) : m_code{code} {}

	bool isError() const { return m_code != ErrorCode::Ok; }
	ErrorCode getError() const { return m_code; }

	/*explicit*/
	operator bool() const { return isError(); }
private:
	ErrorCode m_code;
};

void example() {
	Error error{ErrorCode::NotFound};

	if (error.isError()) {
		std::cout << "We have error!" << std::endl;
	}
	else {
		std::cout << "Everything is good!" << std::endl;
	}

	// Call the Error::operator bool here
	if (error) {
		std::cout << "We have error!" << std::endl;
	}
	else {
		std::cout << "Everything is good!" << std::endl;
	}

	bool isError = static_cast<bool>(error);
}

int main() {
	example();

	return 0;
}