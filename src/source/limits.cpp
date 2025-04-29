#include <algorithm>
#include <iostream>
#include <limits>
#include <string>

#include <cmath>

namespace demo {

	void example() {
		std::cout << "\n*** demo::example(): ***\n";
		std::cout
			<< "type\t| lowest\t| min()\t\t| max()\n"
			<< "bool\t| "
			<< std::numeric_limits<bool>::lowest() << "\t\t| "
			<< std::numeric_limits<bool>::min() << "\t\t| "
			<< std::numeric_limits<bool>::max() << '\n'
			<< "uchar\t| "
			<< +std::numeric_limits<unsigned char>::lowest() << "\t\t| "
			<< +std::numeric_limits<unsigned char>::min() << "\t\t| "
			<< +std::numeric_limits<unsigned char>::max() << '\n'
			<< "int\t| "
			<< std::numeric_limits<int>::lowest() << "\t| "
			<< std::numeric_limits<int>::min() << "\t| "
			<< std::numeric_limits<int>::max() << '\n'
			<< "float\t| "
			<< std::numeric_limits<float>::lowest() << "\t| "
			<< std::numeric_limits<float>::min() << "\t| "
			<< std::numeric_limits<float>::max() << '\n'
			<< "double\t| "
			<< std::numeric_limits<double>::lowest() << "\t| "
			<< std::numeric_limits<double>::min() << "\t| "
			<< std::numeric_limits<double>::max() << '\n';
	}
}

namespace usage1 {

	template <typename T>
	T max(T *array, size_t count) {
		T max = std::numeric_limits<T>::lowest();
		for (size_t i = 0; i < count; ++i) {
			if (max < array[i])
				max = array[i];
		}
		return max;
	}

	void example() {
		std::cout << "\n*** usage1::example(): ***\n";

		int i_array[] = {4, 0, 8, 1, 7, 2, 6, 3, 5, 9};
		int i_max = max(i_array, sizeof(i_array) / sizeof(int));
		std::cout << "max from int array: " << i_max << std::endl;
	}

}

namespace usage2 {

	bool check_int_arg(const char *arg) {
		// Try to parse string as long long
		long long value = std::stoll(arg);
		// The value is incorrect is it > std::numeric_limit<int>::max()
		if (value > std::numeric_limits<int>::max()) {
			return false;
		}
		return true;
	}

	void example() {
		std::cout << "\n*** usage2::example(): ***\n";

		std::cout << "Assume that we have a some program which need int value as an argument" << std::endl;
		std::cout << "How to check it." << std::endl;

		bool correct = check_int_arg("256724");
		std::cout << "correct: " << correct << std::endl;

		bool incorrect = check_int_arg("2147483645800");
		std::cout << "incorrect: " << incorrect << std::endl;
	}

}

namespace hard {

	template <typename T>
	bool simple_check_equal(T a, T b) {
		return a == b;
	}

	template <typename T>
	bool epsilon_check_equal(T a, T b) {
		return std::abs(a - b) <= std::numeric_limits<T>::epsilon();
	}

	template <typename T>
	bool normalize_check_equal(T a, T b) {
		return std::abs(a - b) <= std::numeric_limits<T>::epsilon() *
									  std::max({T{1}, std::abs(a), std::abs(b)});
	}

	void example() {
		std::cout << "\n*** hard::example(): ***\n";

		{
			int a = 10;
			int b = 11;
			bool simple = simple_check_equal(a, b);
			bool epsilon = epsilon_check_equal(a, b);
			bool normalize = normalize_check_equal(a, b);

			std::cout << "The result for ints: " << a << " and " << b << ":"
					  << "\n\tsimple: " << simple
					  << "\n\tepsilon: " << epsilon
					  << "\n\tnormalize: " << normalize;
			std::cout << std::endl;
		}

		{
			double a = 0.2;
			double b = 1 / std::sqrt(5) / std::sqrt(5);
			bool simple = simple_check_equal(a, b);
			bool epsilon = epsilon_check_equal(a, b);
			bool normalize = normalize_check_equal(a, b);

			std::cout << "The result for doubles: " << a << " and " << b << ":"
					  << "\n\tsimple: " << simple
					  << "\n\tepsilon: " << epsilon
					  << "\n\tnormalize: " << normalize;
			std::cout << std::endl;
		}

		{
			double a = 0.2 * 1e10;
			double b = 1 / std::sqrt(5) / std::sqrt(5) * 1e10;
			bool simple = simple_check_equal(a, b);
			bool epsilon = epsilon_check_equal(a, b);
			bool normalize = normalize_check_equal(a, b);

			std::cout << "The result for doubles: " << a << " and " << b << ":"
					  << "\n\tsimple: " << simple
					  << "\n\tepsilon: " << epsilon
					  << "\n\tnormalize: " << normalize;
			std::cout << std::endl;
		}
	}

}

int main() {
	demo::example();
	usage1::example();
	usage2::example();
	hard::example();

	return 0;
}
