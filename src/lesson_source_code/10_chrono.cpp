#include <iostream>
#include <chrono>     // для работы с временем
#include <thread>     // для работы с потоками (для функции sleep)
#include <iomanip>    // для форматирования вывода
#include <vector>
#include <algorithm>
#include <ctime>      //  для работы с системным временем

// Функция для демонстрации измерения времени выполнения
void expensive_operation(int size) {
    std::vector<int> data(size);     // Создание вектора заданного размера
    
    // Заполнение вектора случайными числами
    for (int i = 0; i < size; i++) { // Для каждого элемента
        data[i] = rand() % 1000;     // Генерация случайного числа
    }
    
    // Сортировка вектора
    std::sort(data.begin(), data.end()); // Сортировка всего вектора
}

int main() {
    std::cout << "=== Работа с длительностями времени ===" << std::endl;
    
    // Создание различных длительностей времени
    std::chrono::hours one_hour(1);               // 1 час
    std::chrono::minutes one_minute(1);           // 1 минута
    std::chrono::seconds one_second(1);           // 1 секунда
    std::chrono::milliseconds one_millisecond(1); // 1 миллисекунда
    std::chrono::microseconds one_microsecond(1); // 1 микросекунда
    std::chrono::nanoseconds one_nanosecond(1);   // 1 наносекунда
    
    // Преобразование между разными единицами измерения времени
    std::chrono::seconds seconds_in_hour = std::chrono::duration_cast<std::chrono::seconds>(one_hour); // Преобразование часов в секунды
    std::cout << "Секунд в одном часе: " << seconds_in_hour.count() << std::endl; // Вывод количества секунд
    
    std::chrono::milliseconds ms_in_second = std::chrono::duration_cast<std::chrono::milliseconds>(one_second); // Преобразование секунд в миллисекунды
    std::cout << "Миллисекунд в одной секунде: " << ms_in_second.count() << std::endl; // Вывод количества миллисекунд
    
    // Арифметические операции с длительностями
    auto two_hours = one_hour + one_hour; // Сложение двух длительностей
    std::cout << "Часов в двух часах: " << two_hours.count() << std::endl; // Вывод количества часов
    
    auto half_hour = std::chrono::minutes(30); // 30 минут
    auto hour_and_half = one_hour + half_hour; // Сложение часа и получаса
    
    std::cout << "Минут в полутора часах: " 
              << std::chrono::duration_cast<std::chrono::minutes>(hour_and_half).count() 
              << std::endl; // Вывод количества минут
    
    std::cout << "\n=== Измерение времени выполнения кода ===" << std::endl;
    
    // Измерение времени выполнения функции
    auto start = std::chrono::high_resolution_clock::now(); // Засечка начального времени
    
    // Выполнение дорогостоящей операции
    expensive_operation(100000); // Вызов функции с большим объемом данных
    
    auto end = std::chrono::high_resolution_clock::now(); // Засечка конечного времени
    
    // Вычисление затраченного времени
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // Вычисление длительности
    
    std::cout << "Время выполнения expensive_operation(100000): " 
              << duration.count() << " мс" << std::endl; // Вывод времени выполнения
    
    // Измерение времени выполнения для разных размеров входных данных
    std::vector<int> sizes = {10000, 50000, 100000, 200000}; // Различные размеры для тестирования
    
    for (int size : sizes) { // Для каждого размера
        auto start = std::chrono::high_resolution_clock::now(); // Засечка начального времени
        
        expensive_operation(size); // Вызов функции
        
        auto end = std::chrono::high_resolution_clock::now(); // Засечка конечного времени
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); // Вычисление длительности
        
        std::cout << "Размер: " << std::setw(6) << size 
                  << ", Время: " << std::setw(5) << duration.count() << " мс" 
                  << std::endl; // Вывод размера и времени выполнения
    }
    
    std::cout << "\n=== Работа с моментами времени ===" << std::endl;
    
    // Получение текущего времени
    auto now = std::chrono::system_clock::now(); // Получение текущего системного времени
    
    // Преобразование в time_t для вывода в человеческом формате
    std::time_t current_time = std::chrono::system_clock::to_time_t(now); // Преобразование в time_t
    
    // Вывод текущего времени
    std::cout << "Текущее время: " << std::ctime(&current_time); // Вывод текущего времени
    
    // Создание точки времени в будущем
    auto one_day_later = now + std::chrono::hours(24); // Добавление 24 часов к текущему времени
    std::time_t future_time = std::chrono::system_clock::to_time_t(one_day_later); // Преобразование в time_t
    
    // Вывод времени через день
    std::cout << "Время через 24 часа: " << std::ctime(&future_time); // Вывод будущего времени
    
    // Разница между двумя моментами времени
    auto time_diff = one_day_later - now; // Вычисление разницы между временами
    auto hours_diff = std::chrono::duration_cast<std::chrono::hours>(time_diff).count(); // Преобразование в часы
    
    std::cout << "Разница во времени: " << hours_diff << " часов" << std::endl; // Вывод разницы
    
    std::cout << "\n=== Использование задержек ===" << std::endl;
    
    // Использование sleep для задержки выполнения
    std::cout << "Ожидание 2 секунды..." << std::endl; // Сообщение о начале ожидания
    
    auto delay_start = std::chrono::high_resolution_clock::now(); // Засечка начального времени
    
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Задержка выполнения на 2 секунды
    
    auto delay_end = std::chrono::high_resolution_clock::now(); // Засечка конечного времени
    auto actual_delay = std::chrono::duration_cast<std::chrono::milliseconds>(delay_end - delay_start); // Вычисление фактической задержки
    
    std::cout << "Фактическая задержка: " << actual_delay.count() << " мс" << std::endl; // Вывод фактической задержки
    
    // Задержка до определенного момента времени
    auto delay_until_time = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1); // Вычисление момента времени для задержки
    
    std::cout << "Ожидание до определенного момента времени (1 секунда)..." << std::endl; // Сообщение о начале ожидания
    
    std::this_thread::sleep_until(delay_until_time); // Задержка до указанного момента времени
    
    std::cout << "Ожидание завершено!" << std::endl; // Сообщение о завершении ожидания
    
    std::cout << "\n=== Создание простого таймера ===" << std::endl;
    
    // Простая реализация таймера с обратным отсчетом
    int countdown_seconds = 5; // Количество секунд для обратного отсчета
    
    std::cout << "Начинаем обратный отсчет от " << countdown_seconds << " секунд:" << std::endl; // Сообщение о начале отсчета
    
    for (int i = countdown_seconds; i > 0; i--) { // Цикл обратного отсчета
        std::cout << "Осталось " << i << " сек..." << std::endl; // Вывод оставшегося времени
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Задержка на 1 секунду
    }
    
    std::cout << "Время вышло!" << std::endl; // Сообщение о завершении отсчета
    
    return 0;
}
