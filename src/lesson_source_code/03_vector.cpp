#include <iostream>
#include <vector>  // для работы с векторами

int main() {
    std::vector<int> numbers; // Создание пустого вектора для хранения целых чисел
    
    // Добавление элементов в конец вектора
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(40);

    std::cout << "Размер вектора: " << numbers.size() << std::endl;
    
    // Доступ к элементам вектора по индексу
    std::cout << "Первый элемент: " << numbers[0] << std::endl;
    std::cout << "Последний элемент: " << numbers.back() << std::endl;
    
    // Изменение элемента по индексу
    numbers[1] = 25; // Изменение второго элемента (индекс 1) на значение 25
    
    // Вывод всех элементов вектора с помощью цикла for
    std::cout << "Все элементы вектора:" << std::endl;
    for (size_t i = 0; i < numbers.size(); i++) { // Цикл от 0 до размера вектора
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl; // Вывод элемента по индексу
    }
    
    // Использование цикла for с диапазоном (range-based for, C++11)
    std::cout << "Элементы вектора (через range-based for):" << std::endl;
    for (int my_value : numbers) {    // Для каждого значения в векторе
        std::cout << my_value << " "; // Вывод значения
    }
    std::cout << std::endl;
    
    // Добавление нескольких элементов
    numbers.push_back(40); // Добавление ещё одного элемента
    numbers.push_back(50); // Добавление ещё одного элемента
    
    // Удаление последнего элемента
    numbers.pop_back(); // Удаление последнего элемента (50)
    
    // Проверка, пуст ли вектор
    if (!numbers.empty()) { // Если вектор не пустой
        std::cout << "Вектор содержит " << numbers.size() << " элементов" << std::endl;
    }
    
    // Очистка вектора
    numbers.clear(); // Удаление всех элементов
    std::cout << "После очистки размер вектора: " << numbers.size() << std::endl; // Вывод размера после очистки
    
    return 0;
}
