#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

void compare()
{
    std::string s1{"qwerty"};
    std::string s2{"qwerity"};

    assert(s1 > s2);
    assert(!(s1 < s1) && !(s1 > s1));

    // std::vector<std::vector<std::vector<int>>> vec2d; 
    // vec2d[0][1][3] = 345;

    std::vector<std::string> qwerty = 
        {
           "mystring",
           "qwerty",
           "alphabet",
           "row",
           "column",
           "rowboat",
           "QWerty"
        };

    std::sort(qwerty.begin(), qwerty.end()); // <
    
    std::cout << "Sorted by < operator: " << std::endl;
    for (auto str_item : qwerty)
    {
           std::cout << str_item << std::endl;
    }
}

void find()
{
    // 1
    std::cout << std::endl << "Simple find begin" << std::endl;

    std::string first{"thxyfirst string inn find method"};
    std::string second{"ABBA BABBAB"};
    
    decltype(first.cbegin()) str_iter;
    std::size_t position = 0;
    
    str_iter = std::find(first.cbegin(), first.cend(), 'n');
    position = std::distance(first.cbegin(), str_iter);

    // std::cout << "First 'n' position is: "<< position << "\n";
    // assert(position == first.find('n'));
    
    std::cout << "Simple find end" << std::endl << std::endl;

    // 2
    std::cout << "Find_if begin" << std::endl;

    struct SymbolComparator
    {
        SymbolComparator(const char inputChar):ch_(inputChar) {}       
        bool operator() (char ch) {return ch <= ch_;}
    private:
        char ch_;
    };

    const char ch1('f');
    str_iter = std::find_if(first.cbegin(), first.cend(), SymbolComparator(ch1));

    std::cout << "--> " << *str_iter << std::endl;
    auto pos = std::distance(first.cbegin(), str_iter);
    std::cout << "First greater than " << ch1 << " symbol's position is: "<< pos << std::endl;
    
    const char ch2('f');
    str_iter = std::find_if_not(first.cbegin(), first.cend(), SymbolComparator(ch2));
    pos = std::distance(first.cbegin(), str_iter);
    std::cout << "First lesser or equal to " << ch2 << " symbol's position is: "<< pos << std::endl;;
    
    std::cout << "Find-if end" << std::endl;

    // 3.
    std::cout << " Adjacent find begin" << std::endl;
    str_iter = std::adjacent_find(first.cbegin(), first.cend());
    pos = std::distance(first.cbegin(), str_iter);
    std::cout << "Position of the first symbol in an adjacent pair is: "<< pos << "\n";
    std::cout << first.at(pos) << " " << first.at(pos + 1) << std::endl;
    std::cout << " Adjacent find begin" << std::endl;

    // 4.
    std::cout <<" Find substring " << std::endl;
    std::string eve{"ing"};
    str_iter = std::search(first.cbegin(), first.cend(), eve.cbegin(), eve.cend());
    pos = std::distance(first.cbegin(), str_iter);
    std::cout << R"(Position of the "ing" substring is: )"<< pos << std::endl;

    // 5.    
    std::string bb{"BB"};
    str_iter = std::find_end(second.cbegin(), second.cend(), bb.cbegin(), bb.cend());
    pos = std::distance(second.cbegin(), str_iter);
    std::cout << R"(Position of the last "BB" substring is: )"<< pos << "\n";
    
    // 6.
    std::cout << " Find first symbol from a given set" << std::endl;
    
    std::string origin{"Yet another sEquence of letters"};
    std::string symbols{"l E"};
    str_iter = std::find_first_of(origin.cbegin(), origin.cend(), symbols.cbegin(), symbols.cend());
    pos = std::distance(origin.cbegin(), str_iter);
    std::cout << R"(Position of the first symbol from "l E" set is: )" << pos << std::endl;
    pos = origin.find_first_not_of("Yex a");
    std::cout << R"(Position of the first symbol different from "Yex a" is: )" << pos << std::endl;

    // 7.  
    std::cout << " Find sequence of repeated symbols with certain length" << std::endl;
    
    str_iter = std::search_n(origin.cbegin(), origin.cend(), 2, 't');
    pos = std::distance(origin.cbegin(), str_iter);
    std::cout << "Position of the first symbol in sequence of 2 't' is: " << pos << std::endl;
    
    // 8.
    std::cout << "Strings mismatch" << std::endl;
    std::string s1{"The early bird eats the worm"};
    std::string s2{"The early bird catches the worm"};
    auto ret = std::mismatch(s1.begin(), s1.end(), s2.begin());
    size_t pos1 = std::distance(s1.begin(), ret.first);
    size_t pos2 = std::distance(s2.begin(), ret.second);

    std::cout << "Position of the first  symbol in mismatch is: "<< pos1 << std::endl;
    std::cout << "Position of the second symbol in mismatch is: "<< pos2 << std::endl;
}

int main()
{
    compare();
    find();

    return 0;
}
