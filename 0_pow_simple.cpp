#include <iostream>
#include <iomanip>
#include <math.h>

// Преимущества функций:
// 1. Переиспользование кода
// 2. Структурирование кода
// 3. Возможно делегирования работы
// 4. Удобство тестирования
// 5.

int main()
{

	double base = 0;
	double exp = 0;

	std::cout << "Enter base: ";
	std::cin >> base;
	std::cout << std::endl;

	std::cout << "Enter exp: ";
	std::cin >> exp;
	std::cout << std::endl;

	if (floor(exp) != ceil(exp))
	{
		std::cout << "exp must be an integer" << std::endl;
		return 0;
	}

	double result = 1;
	for (unsigned int i = 0; i < exp; i++)
	{
		std::cout << i << std::endl;
		result *= base;
	}

	std::cout << std::setprecision(10) << "pow(" << base << ", " << exp << ") = " << result << std::endl;
	// pow(3.1415926, 8) = 9488.529721

	return 0;
}