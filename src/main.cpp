#include <iostream>
#include <vector>
#include <algorithm>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& values)
{
    for (auto& v : values)
        os << v << ' ';
    return os;
}

int main()
{
    std::vector<int> target(10, 0);
    std::cout << target << std::endl;
    std::generate(target.begin(), target.end(), [counter = 0]() mutable {return counter += 2;});
    std::cout << target << std::endl;
    return 0;
}
