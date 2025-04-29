#include <iostream>
#include <vector>    // для работы с векторами
#include <algorithm> // для работы с алгоритмами

int main() {
    std::vector<int> numbers = {-434, 2, 3, 3, 1, 9, 44445, 7, 4, 6, 3, 7, 4};
    
    // Вывод исходного вектора
    std::cout << "Исходный вектор: ";
    for (int num : numbers) {    // Для каждого числа в векторе
        std::cout << num << " "; // Вывод числа
    }
    std::cout << std::endl;
    
    // Сортировка вектора по возрастанию
    std::sort(numbers.begin(), numbers.end()); // Сортировка всего вектора от начала до конца
    
    // Вывод отсортированного вектора
    std::cout << "Отсортированный вектор: ";
    for (int num : numbers) {     // Для каждого числа в векторе
        std::cout << num << " ";  // Вывод числа
    }
    std::cout << std::endl;
    
    // Поиск элемента в векторе
    int target = 950;  // Искомое значение
    auto it = std::find(numbers.begin(), numbers.end(), target); // Поиск элемента в векторе
    
    if (it != numbers.end()) { // Если элемент найден (итератор не указывает на конец)
        std::cout << "Элемент " << target << " найден в позиции: " 
                 << std::distance(numbers.begin(), it) << std::endl; // Вывод позиции элемента
    } else { // Если элемент не найден
        std::cout << "Элемент " << target << " не найден" << std::endl; // Сообщение о том, что элемент не найден
    }
    
    // Подсчет количества элементов, удовлетворяющих условию
    int count_greater_than_5 = std::count_if(numbers.begin(), numbers.end(), 
                                           [](int x) { return x > 5; }); // Подсчет элементов больше 5
    std::cout << "Количество элементов больше 5: " << count_greater_than_5 << std::endl; // Вывод результата
    
    // Нахождение минимального и максимального элементов
    auto [min_it, max_it] = std::minmax_element(numbers.begin(), numbers.end()); // Поиск минимального и максимального элементов
    std::cout << "Минимальный элемент: " << *min_it << std::endl;   // Вывод минимального элемента
    std::cout << "Максимальный элемент: " << *max_it << std::endl;  // Вывод максимального элемента
    
    // Сортировка по убыванию
    std::sort(numbers.begin(), numbers.end(), std::greater<int>()); // Сортировка вектора по убыванию
    
    // Вывод вектора, отсортированного по убыванию
    std::cout << "Вектор, отсортированный по убыванию: ";
    for (int num : numbers) {     // Для каждого числа в векторе
        std::cout << num << " ";  // Вывод числа
    }
    std::cout << std::endl;
    
    // Заполнение части вектора одинаковым значением
    std::fill(numbers.begin(), numbers.begin() + 7, 0); // Заполнение первых трех элементов нулями
    
    // Вывод вектора после заполнения
    std::cout << "Вектор после заполнения: ";
    for (int num : numbers) {     // Для каждого числа в векторе
        std::cout << num << " ";  // Вывод числа
    }
    std::cout << std::endl;
    
    return 0;
}
