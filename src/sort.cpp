#include <algorithm>
#include <iostream>
#include <list>
#include <random>
#include <vector>
#include <tuple>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &values) {
	for (const auto &v : values) {
		std::cout << v << ' ';
	}
	return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::list<T> &values) {
	for (const auto &v : values) {
		std::cout << v << ' ';
	}
	return os;
}

struct CompareTracer {
	CompareTracer(int value)
		: m_value{value} {
	}

	static void reset() {
		m_counter = 0;
	}

	bool operator<(const CompareTracer &other) const {
		std::cout << "Compare: " << m_value << " < " << other.m_value << std::endl;
		++m_counter;
		return m_value < other.m_value;
	}

	bool operator==(const CompareTracer &other) const {
		std::cout << "Compare: " << m_value << " == " << other.m_value << std::endl;
		++m_counter;
		return m_value == other.m_value;
	}

	bool operator>(const CompareTracer &other) const {
		std::cout << "Compare: " << m_value << " > " << other.m_value << std::endl;
		++m_counter;
		return m_value > other.m_value;
	}

	static std::size_t getCounter() {
		return m_counter;
	}

	friend std::ostream &operator<<(std::ostream &os, const CompareTracer &v) {
		os << v.m_value;
		return os;
	}

private:
	static std::size_t m_counter;
	int m_value;
};
std::size_t CompareTracer::m_counter = 0;

void test_sort() {
	std::cout << "\ntest_sort\n";

	std::vector<CompareTracer> source = {{9}, {8}, {7}, {6}, {5}, {4}, {3}, {2}, {1}, {0}};

	// bool is_sorted( ForwardIt first, ForwardIt last, Compare comp );

	std::cout << "is_sorted = " << std::is_sorted(source.cbegin(), source.cend(), std::greater<>()) << std::endl
			  << std::endl;

	std::random_shuffle(source.begin(), source.end());
	std::vector<CompareTracer> target1 = source;

	std::cout << "Values before sorting:\n";
	std::cout << target1 << std::endl
			  << std::endl;

	// void sort( RandomIt first, RandomIt last, Compare comp );

	std::sort(target1.begin(), target1.end());	// std::less - a < b < c < d
																							// std::greater - a > b > c > d
	// Complexity: O(N·log(N)), where N = std::distance(first, last) comparisons.

	std::cout << "Compares count = " << CompareTracer::getCounter() << std::endl;
	CompareTracer::reset();

	std::cout << "target1 after sort:\n";
	std::cout << target1 << std::endl
			  << std::endl;

	std::vector<CompareTracer> target2 = source;

	// void partial_sort( RandomIt first, RandomIt middle, RandomIt last, Compare comp );

	std::partial_sort(target2.begin(), std::next(target2.begin(), 3), target2.end());
	// Complexity: Approximately (last-first)log(middle-first) applications of cmp.

	std::cout << "Compares count = " << CompareTracer::getCounter() << std::endl;
	CompareTracer::reset();

	std::cout << "target2 after partial_sort:\n";
	std::cout << target2 << std::endl
			  << std::endl;

	std::vector<CompareTracer> target3 = source;
	std::nth_element(target3.begin(), std::next(target3.begin(), target3.size() / 2), target3.end());

	std::cout << "target3 after nth_element:\n";
	std::cout << target3 << std::endl;
	std::cout << "Compares count = " << CompareTracer::getCounter() << std::endl;
	CompareTracer::reset();
	std::cout << std::endl;

	using Record = std::tuple<int, int, int>;
	std::vector<Record> target4 = {
		{9, 0, 100},
		{9, 1, 200},
		{9, 1, 300},
		{9, 3, 200},
		{9, 4, 300},
		{8, 1, 100},
		{8, 1, 300},
		{8, 2, 100},
		{7, 0, 100},
		{6, 0, 400},
		{5, 0, 200},
	};

	std::cout << "target4 before stable sort:  ";
	for (const auto &p : target4) {
		std::cout << '[' << std::get<0>(p) << ", " << std::get<1>(p) << ", " << std::get<2>(p) << "] ";
	}
	std::cout << std::endl;

	std::sort(
		target4.begin(),
		target4.end(),
		[](const Record &l, const Record &r) {
			return std::get<0>(l) < std::get<0>(r);
		});

	std::cout << "target4 after        sort 1: ";
	for (const auto &p : target4) {
		std::cout << '[' << std::get<0>(p) << ", " << std::get<1>(p) << ", " << std::get<2>(p) << "] ";
	}
	std::cout << std::endl;
	
	
	std::stable_sort(
		target4.begin(),
		target4.end(),
		[](const Record &l, const Record &r) {
			return std::get<1>(l) < std::get<1>(r);
		});

	std::cout << "target4 after stable sort 2: ";
	for (const auto &p : target4) {
		std::cout << '[' << std::get<0>(p) << ", " << std::get<1>(p) << ", " << std::get<2>(p) << "] ";
	}
	std::cout << std::endl;
	
	std::stable_sort(
		target4.begin(),
		target4.end(),
		[](const Record &l, const Record &r) {
			return std::get<2>(l) < std::get<2>(r);
		});

	std::cout << "target4 after stable sort 3: ";
	for (const auto &p : target4) {
		std::cout << '[' << std::get<0>(p) << ", " << std::get<1>(p) << ", " << std::get<2>(p) << "] ";
	}
	std::cout << std::endl;
}

void test_list() {
	std::cout << "\ntest_list\n";

	std::list<int> values = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

	std::cout << "Values before sorting:\n";
	std::cout << values << std::endl
			  << std::endl;

	// std::sort(values.begin(), values.end());

	values.sort();
	// Complexity: Approximately N log N comparisons, where N is the number of elements in the list.

	std::cout << "Values after sorting:\n";
	std::cout << values << std::endl
			  << std::endl;

	// No such methods
	// values.stable_sort();
	// values.partial_sort();
}

int main() {
	test_sort();
	test_list();

	return 0;
}