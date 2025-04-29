#include <chrono>
#include <iostream>

using namespace std::chrono;

/*constexpr */ long double operator"" _deg_to_rad(long double deg) {
	const long double pi = 3.14159265358979323846;
	long double radians = deg * pi / 180;
	return radians;
}

int main() {
	// 1.
	double x_rad = 90.0_deg_to_rad;
	std::cout << x_rad << '\n';

	// 2.
	std::chrono::seconds sec(5);
	auto secs = 5s;

	seconds time1 = 5min + 17s;
	minutes time2 = 2h - 15min;
	std::cout << time2.count() << std::endl;

	seconds s = 15s;
	std::cout << s.count() << "s\n";

	// timepoint
	auto start = steady_clock::now();
	std::cout << "Timeout string printed to measure time" << std::endl;
	auto end = steady_clock::now();
	auto elapsed = duration_cast<microseconds>(end - start);
	std::cout << elapsed.count() << std::endl;

	return 0;
}