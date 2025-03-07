#include <iostream>
#include <string>

namespace classes {

    class Biometrics_bad {
        // private by default
        int one;
        int another;
        // ...
    };

    void test() {
        Biometrics_bad bio;
        // bio.one = 42; // error: 'one' is a private member of 'classes::Biometrics_bad'
        // bio.another = 24;  // error: 'another' is a private member of 'classes::Biometrics_bad'
    }

    class Biometrics {
    public:
        int one;
        int another;
        // ...
    };

    class Person {
    public:
        std::string name;
        std::string surname = "Ivanov";
        int age;

        void set_bio(const Biometrics &bio) {
            m_bio = bio;
        }
        const Biometrics &get_bio() const {
            return m_bio;
        }

    private:
        Biometrics m_bio;
    };

    Biometrics get_user_biometrics() {
        Biometrics bio;
        bio.one = 42;
        bio.another = 24;
        return bio;
    }

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

        Biometrics bio = get_user_biometrics();
        person.set_bio(bio);

        return person;
    }

    void example() {
        const Person person = get_user_info();

        if (person.age < 16) {
            std::cout << "Access denied!" << '\n';
        } else if (person.age < 30) {
            std::cout << "Hello, " << person.name << '\n';
        } else {
            std::cout << "Hello, " << person.name << " " << person.surname << '\n';
        }

        person.get_bio(); // do something with bio
    }

} // namespace classes

int main() {

    classes::example();
}
