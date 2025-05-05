// Ссылка на репозиторий OpenSSL для справок
// https://github.com/openssl/openssl.git

// Заголовочный файл для работы с хеш-функциями OpenSSL
#include <openssl/evp.h>

// Стандартные заголовки C++
#include <iostream>
#include <sstream>   // Строковые потоки
#include <iomanip>   // Манипуляторы вывода
#include <string_view> // Представление строк без копирования
#include <memory>    // Умные указатели

// Функция вычисления хеша сообщения
// Возвращает true/false в зависимости от успеха операции
// Результат записывается в динамически выделенный буфер digest
bool digest_message(
    const char* message,     // Входное сообщение
    size_t message_len,       // Длина сообщения
    unsigned char** digest,   // Указатель на буфер для хеша (выделяется внутри)
    unsigned int* digest_len) // Указатель на длину хеша
{
    // Лямбда для безопасного освобождения контекста хеширования
    // (используется в unique_ptr как кастомный делитер)
    const auto releaseContext = [](EVP_MD_CTX* const context) {
        if (context == NULL) return;
        EVP_MD_CTX_free(context); // Освобождение памяти контекста
    };

    // Умный указатель с кастомным делитером для автоматической очистки контекста
    std::unique_ptr<EVP_MD_CTX, decltype(releaseContext)> context(
        EVP_MD_CTX_new(),    // Создание нового контекста
        releaseContext);

    if (!context) return false; // Проверка успешности создания контекста

    // Инициализация контекста алгоритмом SHA-256
    if (EVP_DigestInit_ex(&*context, EVP_sha256(), NULL) != 1)
        return false; // Ошибка инициализации

    // Добавление сообщения в контекст хеширования
    if (EVP_DigestUpdate(&*context, message, message_len) != 1)
        return false; // Ошибка обновления данных

    // Выделение памяти под результат хеша через OpenSSL
    *digest = static_cast<unsigned char*>(
        OPENSSL_malloc(EVP_MD_size(EVP_sha256()))); // Размер для SHA-256

    if (*digest == NULL) return false; // Проверка выделения памяти

    // Завершение хеширования и запись результата в выделенный буфер
    if (EVP_DigestFinal_ex(&*context, *digest, digest_len) != 1)
        return false; // Ошибка финализации

    return true; // Успешное выполнение
}

// Функция-обертка для получения хеша в виде строки
std::string sha256(const std::string_view& str) {
    using namespace std;

    unsigned char* digest = nullptr;  // Буфер для бинарного хеша
    unsigned int digest_len = 0;      // Длина хеша

    // Вычисление хеша через digest_message
    if (!digest_message(str.data(), str.size(), &digest, &digest_len)) {
        OPENSSL_free(digest);         // Очистка в случае ошибки
        throw runtime_error("Failed to digest message");
    }

    stringstream ss; // Поток для форматирования вывода

    // Преобразование бинарного хеша в HEX-строку
    for (size_t i = 0; i < digest_len; i++) {
        // Форматирование: 2 символа, ведущие нули, шестнадцатеричные
        ss << hex << setw(2) << setfill('0') << (int)digest[i];
    }

    OPENSSL_free(digest); // Освобождение выделенной OpenSSL памяти
    return ss.str();      // Возврат форматированной строки
}

int main() {
    // Пример использования: вывод SHA-256 для строки "Hello world!"
    std::cout << sha256("Hello world!") << '\n';
}