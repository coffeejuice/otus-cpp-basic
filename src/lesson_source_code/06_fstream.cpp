#include <iostream>
#include <fstream>  // для работы с файлами
#include <string>
#include <vector>

int main() {
    // Запись в файл
    std::ofstream my_file("example.txt"); // Создание файлового потока для записи
    
    if (my_file.is_open()) { // Проверка, открылся ли файл успешно
        my_file << "Это первая строка файла." << std::endl; // Запись 1 строки 
        my_file << "Это вторая строка файла." << std::endl; // Запись 2 строки 
        my_file << "Число: " << 12345 << std::endl; // Запись числа в файл
        
        my_file.close();  // Закрытие файла после записи
    } else {
        std::cerr << "Ошибка при открытии файла для записи!" << std::endl; 
        return 1;
    }
    
    // Файловый поток для чтения из файла построчно
    std::ifstream input_file("example.txt");
    
    if (input_file.is_open()) {          // Проверка, открылся ли файл успешно
        std::string line;                // Переменная для хранения считываемой строки
        std::vector<std::string> lines;  // Вектор для хранения всех строк файла
        
        std::cout << "Содержимое файла (построчное чтение):" << std::endl;
        
        while (std::getline(input_file, line)) {  // Считывание файла построчно
            std::cout << line << std::endl; // Вывод считанной строки
            lines.push_back(line); // Добавление строки в вектор
        }
        
        input_file.close(); // Закрытие файла после чтения
        
        // Вывод количества строк в файле
        std::cout << "Всего строк в файле: " << lines.size() << std::endl;
        
        // Вывод третьей строки, если она существует
        if (lines.size() >= 3) { // Если в файле есть хотя бы 3 строки
            std::cout << "Третья строка: " << lines[2] << std::endl; // Вывод третьей строки
        }
    } else { // Если файл не удалось открыть
        std::cerr << "Ошибка при открытии файла для чтения!" << std::endl;
        return 1;
    }
    
    // Чтение из файла по символам
    input_file.open("example.txt");  // Повторное открытие файла для чтения
    
    if (input_file.is_open()) { // Проверка, открылся ли файл успешно
        char c; // Переменная для хранения считываемого символа
        int char_count = 0; // Счетчик символов
        
        std::cout << "Подсчет символов в файле:" << std::endl;
        
        while (input_file.get(c)) { // Считывание файла посимвольно
            char_count++; // Увеличение счетчика символов
        }
        
        input_file.close(); // Закрытие файла после чтения
        
        // Вывод количества символов в файле
        std::cout << "Всего символов в файле: " << char_count << std::endl;
    } else { // Если файл не удалось открыть
        std::cerr << "Ошибка при открытии файла для подсчета символов!" << std::endl;
        return 1;
    }
    
    // Запись в файл в бинарном режиме
    std::ofstream binary_file("data.bin", std::ios::binary); // Создание файлового потока для бинарной записи
    
    if (binary_file.is_open()) { // Проверка, открылся ли файл успешно
        int numbers[] = {1, 2, 3, 4, 5}; // Массив для записи в файл
        binary_file.write(reinterpret_cast<char*>(numbers), sizeof(numbers)); // Запись массива в бинарный файл
        binary_file.close(); // Закрытие файла после записи
        
        std::cout << "Бинарные данные успешно записаны в файл." << std::endl; // Сообщение об успешной записи
    } else { // Если файл не удалось открыть
        std::cerr << "Ошибка при открытии бинарного файла для записи!" << std::endl; // Вывод сообщения об ошибке
        return 1; // Возврат кода ошибки
    }
    
    // Чтение из файла в бинарном режиме
    std::ifstream binary_input("data.bin", std::ios::binary); // Создание файлового потока для бинарного чтения
    
    if (binary_input.is_open()) { // Проверка, открылся ли файл успешно
        int read_numbers[5]; // Массив для чтения из файла
        binary_input.read(reinterpret_cast<char*>(read_numbers), sizeof(read_numbers)); // Чтение из бинарного файла
        binary_input.close(); // Закрытие файла после чтения
        
        // Вывод прочитанных данных
        std::cout << "Прочитанные бинарные данные: ";
        for (int i = 0; i < 5; i++) { // Для каждого элемента массива
            std::cout << read_numbers[i] << " "; // Вывод элемента
        }
        std::cout << std::endl;
    } else { // Если файл не удалось открыть
        std::cerr << "Ошибка при открытии бинарного файла для чтения!" << std::endl;
        return 1;
    }
    
    return 0;
}
