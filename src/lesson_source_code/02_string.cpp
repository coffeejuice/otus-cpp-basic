#include <iostream> // для работы с вводом-выводом
#include <string>   // для работы со строками

int main() {
    std::string init_text = "Привет всем, и отдельный привет тебе";
    std::string user_name;
    
    std::cout << "Введите имя: ";               // Запрос имени у пользователя
    std::getline(std::cin, user_name);  // Считывание строки (включая пробелы)

    // Конкатенация (объединение) строк
    std::string full_greeting = init_text + ", " + user_name + "!";
    std::cout << full_greeting << std::endl;
    
    std::cout << "Длина строки: " << user_name.length() <<  std::endl;
    std::cout << "Первый символ: " << full_greeting[0] << std::endl;
    std::cout << "Последний символ: " << full_greeting.back() << std::endl;

    // Поиск подстроки в строке
    if (full_greeting.find(user_name) != std::string::npos) { // Если имя найдено в приветствии
        std::cout << "Имя найдено в позиции: " << full_greeting.find(user_name) << std::endl;
    }
    
    // Замена части строки
    full_greeting.replace(0, init_text.length(), "Здравствуйте");
    std::cout << "Измененная строка: " << full_greeting << std::endl;
    
    return 0;
}
