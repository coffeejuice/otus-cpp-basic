#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

#include <cassert>

using namespace std::literals;

// https://regex101.com
void regex() {
	std::cout << "#####Regex compilation######" << std::endl;
	try {
		static const auto r = std::regex(R"(\)"); // Escape sequence error
	} catch (const std::regex_error &e) {
		assert(strcmp(e.what(), "Unexpected end of regex when escaping.") == 0);
		assert(e.code() == std::regex_constants::error_escape);
	}
}

void search() {
	std::cout << "#####Search#####" << std::endl;
	const std::string input = "ABC:1->   PQR:2;;;   XYZ:3<<<"s;
	const std::regex r(R"((\w+):(\w+);)");
	std::smatch m;

	if (regex_search(input, m, r)) {
		assert(m.size() == 3);
		assert(m[0].str() == "PQR:2;");				 // Entire match
		assert(m[1].str() == "PQR");				 // Substring that matches 1st group
		assert(m[2].str() == "2");					 // Substring that matches 2nd group
		assert(m.prefix().str() == "ABC:1->   ");	 // All before 1st character match
		assert(m.suffix().str() == ";;   XYZ:3<<<"); // All after last character match

		for (std::string &&str : m) { // Alternatively. You can also do
			std::cout << str << std::endl;
		}
	}
}

void match() {
	std::cout << "#####Match#####" << std::endl;
	std::string email = "pupkin@mail.ru";
	static const std::regex r(R"(\w+@\w+\.(?:com|in|ru))");
	std::cout << "Email matach " << regex_match(email, r) << std::endl;
}

void search_vs_match() {
	std::cout << "#####search_vs_match######" << std::endl;
	const std::string input = "ABC:1->   PQR:2;;;   XYZ:3<<<"s;
	const std::regex r(R"((\w+):(\w+);)");
	std::smatch m;

	assert(regex_match(input, m, r) == false);

	assert(regex_search(input, m, r) == true && m.ready() == true && m[1] == "PQR");
}

void iterator() {
	std::cout << "#####Iterator#####" << std::endl;
	std::string s("this subject has a submarine as a subsequence");
	std::regex e("\\b(sub)([^ ]*)"); // matches words beginning by "sub"

	std::regex_iterator<std::string::iterator> rit(s.begin(), s.end(), e);
	std::regex_iterator<std::string::iterator> rend;

	while (rit != rend) {
		std::cout << rit->str() << std::endl;
		++rit;
	}
}

void token_iterator() {
	std::cout << "#####Token iterator#####" << std::endl;
	const std::string input = "ABC:1->   PQR:2;;;   XYZ:3<<<"s;
	const std::regex r(R"((\w+):(\d))");

	// Note: vector<string> here, unlike vector<smatch> as in std::regex_iterator
	const std::vector<std::string> full_match{
		std::sregex_token_iterator{cbegin(input), cend(input), r, 0}, // Mark `0` here i.e. whole regex match
		std::sregex_token_iterator{}};
	assert((full_match == decltype(full_match){"ABC:1", "PQR:2", "XYZ:3"}));

	const std::vector<std::string> cptr_grp_1st{
		std::sregex_token_iterator{cbegin(input), cend(input), r, 1}, // Mark `1` here i.e. 1st capture group
		std::sregex_token_iterator{}};
	assert((cptr_grp_1st == decltype(cptr_grp_1st){"ABC", "PQR", "XYZ"}));

	const std::vector<std::string> cptr_grp_2nd{
		std::sregex_token_iterator{cbegin(input), cend(input), r, 2}, // Mark `2` here i.e. 2nd capture group
		std::sregex_token_iterator{}};
	assert((cptr_grp_2nd == decltype(cptr_grp_2nd){"1", "2", "3"}));
}

void replace() {
	std::cout << "#####Replace#####" << std::endl;
	static const auto r = std::regex(R"((\w+):(\d))");
	assert(regex_replace("ABC:1, PQR:2"s, r, "$2") == "1, 2"s);
}

std::vector<std::string> split(const std::string &str, std::string_view pattern) {
	const auto r = std::regex(pattern.data());
	return std::vector<std::string>{
		std::sregex_token_iterator(cbegin(str), cend(str), r, -1),
		std::sregex_token_iterator()};
}

std::string trim(std::string_view text) {
	static const auto r = std::regex(R"(\s+)");
	return std::regex_replace(text.data(), r, "");
}

int main() {
	// regex();
	search();
	match();
	iterator();
	token_iterator();
	replace();

	assert((split("/root/home/vishal", "/") == std::vector<std::string>{"", "root", "home", "vishal"}));

	assert(trim("12   3 4      5"s) == "12345"s);

	return 0;
}
