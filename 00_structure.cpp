#include <iostream>
#include <string>

namespace motivation {

    void example() {
        std::cout << "Hello!" << std::endl;

        std::string name;
        std::cout << "Enter your name:" << std::endl;
        std::cin >> name;

        std::string surname;
        std::cout << "Enter your surname:" << std::endl;
        std::cin >> surname;

        int age{};
        std::cout << "Enter your age:" << std::endl;
        std::cin >> age;

        if (age < 16) {
            std::cout << "Access denied!" << '\n';
        } else if (age < 30) {
            std::cout << "Hello, " << name << '\n';
        } else {
            std::cout << "Hello, " << name << " " << surname << '\n';
        }
    }

    // in - input parameter
    // out - output parameter
    // in/out - input/output parameter
    void get_user_info(std::string &name, std::string &surname, int &age) {
        std::cout << "Hello!" << std::endl;

        std::cout << "Enter your name:" << std::endl;
        std::cin >> name;

        std::cout << "Enter your surname:" << std::endl;
        std::cin >> surname;

        std::cout << "Enter your age:" << std::endl;
        std::cin >> age;
    }

    void example_with_function() {
        std::string name;
        std::string surname;
        int age{};

        get_user_info(name, surname, age);

        if (age < 16) {
            std::cout << "Access denied!" << '\n';
        } else if (age < 30) {
            std::cout << "Hello, " << name << '\n';
        } else {
            std::cout << "Hello, " << name << " " << surname << '\n';
        }
    }

} // namespace motivation

namespace structs {

    struct Person {
        std::string name;
        std::string surname;
        int age;
    };

    Person get_user_info() {
        Person person;

        std::cout << "Hello!" << std::endl;

        std::cout << "Enter your name:" << std::endl;
        std::cin >> person.name;

        std::cout << "Enter your surname:" << std::endl;
        std::cin >> person.surname;

        std::cout << "Enter your age:" << std::endl;
        std::cin >> person.age;

        return person;
    }

    void example() {
        Person person = get_user_info();

        if (person.age < 16) {
            std::cout << "Access denied!" << std::endl;
        } else if (person.age < 30) {
            std::cout << "Hello, " << person.name << std::endl;
        } else {
            std::cout << "Hello, " << person.name << " " << person.surname << std::endl;
        }
    }

} // namespace structs

namespace nested {

    struct Biometrics {
        int one;
        int another;
        // ...
    };

    struct Person {
        std::string name;
        std::string surname = "Ivanov";
        int age;

        Biometrics bio;
    };

    Biometrics get_user_biometrics() {
        Biometrics bio;
        bio.one = 42;
        bio.another = 24;
        return bio;
    }

    // Метод возвращает объект класса
    Person get_user_info() {
        // Объект типа Person
        // Объект - это конкретный экземпляр класса
        Person person;

        std::cout << "Hello!" << '\n';

        std::cout << "Enter your name:" << '\n';
        // Обращаемся к полю класса через оператор .
        std::cin >> person.name;

        std::cout << "Enter your surname:" << '\n';
        std::cin >> person.surname;

        std::cout << "Enter your age:" << '\n';
        std::cin >> person.age;

        person.bio = get_user_biometrics();

        return person;
    }

    void example() {
        const Person person = get_user_info();

        // person - константный объект: можем читать, не можем изменять
        if (person.age < 16) {
            std::cout << "Access denied!" << '\n';
        } else if (person.age < 30) {
            std::cout << "Hello, " << person.name << '\n';
        } else {
            std::cout << "Hello, " << person.name << " " << person.surname << '\n';
        }
    }

} // namespace nested

int main() {

    motivation::example();
    motivation::example_with_function();

    structs::example();

    nested::example();
}
