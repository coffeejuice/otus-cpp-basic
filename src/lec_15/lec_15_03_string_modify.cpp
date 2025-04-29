#include <iostream>
#include <string>

void modify()
{
    {
        std::cout << " Copy and Substr " << std::endl;
        std::string chemicals{"Argentum Mercury Ferrum"};

        auto mercury = chemicals.substr(chemicals.find('M'), 7);
        std::cout << "C++ string: " << mercury << "\n";

        char ferrum[7]{};
        chemicals.copy(ferrum, 6, chemicals.find('F'));
        std::cout << "C string: " << ferrum << std::endl;;
    }
    
    {
        std::cout << std::endl << " Replace " << std::endl;
        std::string chemicals{"Argentum Mercury Ferrum"};

        auto mPos = chemicals.find('M');
        chemicals.replace(chemicals.begin(), chemicals.begin() + mPos, "Elements:");
        std::cout << "New string: " << chemicals << " pos = "<< mPos << std::endl;

        auto fPos = chemicals.find('F');
        chemicals.replace(chemicals.begin() + fPos - 1, chemicals.end(), ", Freddie");
        std::cout << "New string: " << chemicals << "\n";
    }
}

void convertions()
{
    std::cout << " Convertions " << std::endl;
    std::string one{"1"};
    std::string fifteen{"F"};
    std::string fourteen{"1110"};
    double real = 12.567890;
    
    std::cout << "One to integer: " << std::stoi(one) << "\n";
    std::cout << "Fifteen to integer: " << std::stol(fifteen, nullptr, 16) << "\n";
    std::cout << "Fourteen to integer: " << std::stoull(fourteen, nullptr, 2) << "\n";
    std::cout << "Real to string: " << std::to_string(real) << "\n";
}

int main()
{
    modify();
    convertions();

    return 0;
}
