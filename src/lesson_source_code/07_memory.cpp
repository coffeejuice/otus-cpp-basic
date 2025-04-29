#include <iostream>
#include <memory>    // для работы с умными указателями
#include <string>
#include <vector>

// Объявление класса для примера
class Person {
private:
    std::string name;  // Приватное поле для хранения имени
    int age;           // Приватное поле для хранения возраста

public:
    // Конструктор с параметрами
    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Создан объект Person: " << name << ", " << age << " лет" << std::endl;
    }
    
    // Деструктор
    ~Person() {
        std::cout << "Удален объект Person: " << name << std::endl;
    }
    
    // Метод для вывода информации о человеке
    void display() const {
        std::cout << "Имя: " << name << ", Возраст: " << age << " лет" << std::endl; // Вывод информации
    }
    
    // Метод для изменения возраста
    void birthday() {
        age++; // Увеличение возраста на 1
        std::cout << name << " теперь " << age << " лет!" << std::endl; // Вывод сообщения
    }
};

int main() {
    // // Использование unique_ptr - эксклюзивное владение объектом
    // {
    //     std::cout << "=== Пример unique_ptr ===" << std::endl;
    //
    //     // Создание unique_ptr для объекта Person
    //     std::unique_ptr<Person> person1 = std::make_unique<Person>("Иван", 25);
    //
    //     // Использование объекта через умный указатель
    //     person1->display();  // Вызов метода объекта
    //     person1->birthday(); // Вызов метода объекта
    //
    //     // Проверка, не является ли указатель нулевым
    //     if (person1) { // Если указатель не нулевой
    //         std::cout << "person1 указывает на объект" << std::endl; // Вывод сообщения
    //     }
    //
    //     // Явное освобождение ресурса
    //     person1.reset(); // Освобождение ресурса (вызов деструктора Person)
    //
    //     // Проверка после сброса
    //     if (!person1) { // Если указатель нулевой
    //         std::cout << "person1 больше не указывает на объект" << std::endl; // Вывод сообщения
    //     }
    //
    //     // Создаем новый объект
    //     person1 = std::make_unique<Person>("Мария", 30); // Создание нового умного указателя
    //
    //     // Невозможно скопировать unique_ptr
    //     // std::unique_ptr<Person> person2 = person1; // Это бы вызвало ошибку компиляции
    //
    //     // Но можно передать владение (перемещение)
    //     std::unique_ptr<Person> person2 = std::move(person1); // Перемещение владения от person1 к person2
    //
    //     // Теперь person1 пуст, а person2 владеет объектом
    //     if (!person1 && person2) { // Если person1 нулевой, а person2 не нулевой
    //         std::cout << "Владение передано от person1 к person2" << std::endl; // Вывод сообщения
    //         person2->display(); // Вызов метода объекта через person2
    //     }
    //
    // } // person2 автоматически уничтожит объект Person при выходе из области видимости

    // Использование shared_ptr - совместное владение объектом
    {
        std::cout << "\n=== Пример shared_ptr ===" << std::endl;
        std::shared_ptr<Person> person3 = std::make_shared<Person>("Алексей", 40);
        std::cout << "Количество владельцев: " << person3.use_count() << std::endl;
        std::shared_ptr<Person> person4 = person3;
        std::cout << "Количество владельцев после копирования: " << person3.use_count() << std::endl; // Вывод количества владельцев
        person3->display();
        person4->birthday();
        person3->display();
        std::vector<std::shared_ptr<Person>> people;
        people.push_back(person3);
        std::cout << "Количество владельцев после добавления в вектор: " << person3.use_count() << std::endl; // Вывод количества владельцев
        person3.reset();
        std::cout << "Количество владельцев после сброса person3: " << person4.use_count() << std::endl; // Вывод количества владельцев
        person4->display();
        
    } // Все shared_ptr автоматически уничтожаются при выходе из области видимости




    
    return 0;
}
