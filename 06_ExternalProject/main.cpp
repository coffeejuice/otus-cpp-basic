// Пример использования OpenSSL для вычисления хеш-суммы SHA256
// https://github.com/openssl/openssl.git
#include <openssl/evp.h>  // Библиотека криптографических функций OpenSSL

#include <iostream>
#include <sstream>       // Для форматирования строк через потоки
#include <iomanip>       // Для манипуляторов вывода (hex, setw и т.д.)
#include <string_view>   // Для эффективной работы со строками
#include <memory>        // Для умных указателей (unique_ptr)

// Функция вычисления дайджеста сообщения
// message - входные данные, digest - результат хеширования (выделяется через OPENSSL_malloc)
bool digest_message(
    const char* message,
    size_t message_len,
    unsigned char** digest,
    unsigned int* digest_len) {

  // Лямбда для безопасного освобождения контекста хеширования
  const auto releaseContext = [](EVP_MD_CTX* const context) {
    if (context == NULL) return; // Проверка на случай нулевого указателя
    EVP_MD_CTX_free(context);    // Освобождение ресурсов контекста
  };

  // Создаем умный указатель с кастомным делитером для автоматической очистки
  std::unique_ptr<EVP_MD_CTX, decltype(releaseContext)> context(
      EVP_MD_CTX_new(), releaseContext); // Выделение памяти под контекст
  if (!context) { // Проверка успешности создания контекста
    return false;
  }

  // Инициализация контекста для алгоритма SHA256
  if (EVP_DigestInit_ex(&*context, EVP_sha256(), NULL) != 1) {
    return false; // Ошибка инициализации
  }

  // Добавление данных для хеширования в контекст
  if (EVP_DigestUpdate(&*context, message, message_len) != 1) {
    return false; // Ошибка обновления данных
  }

  // Выделение памяти под результат хеширования (размер для SHA256 = 32 байта)
  *digest = static_cast<unsigned char*>(
      OPENSSL_malloc(EVP_MD_size(EVP_sha256())));
  if (digest == NULL) { // Проверка выделения памяти
    return false;
  }

  // Завершение хеширования и запись результата в выделенный буфер
  if (EVP_DigestFinal_ex(&*context, *digest, digest_len) != 1) {
    return false; // Ошибка финализации
  }

  return true; // Успешное выполнение
}

// Функция-обертка для преобразования строки в SHA256-хеш
std::string sha256(const std::string_view& str) {
  using namespace std;

  unsigned char* digest = nullptr;  // Буфер для бинарного представления хеша
  unsigned int digest_len = 0;      // Длина хеша в байтах (32 для SHA256)

  // Вычисление хеша через digest_message
  if (!digest_message(str.data(), str.size(), &digest, &digest_len)) {
    throw std::runtime_error("Filed to digest message"); // Обработка ошибок
  }

  // Преобразование бинарных данных в шестнадцатеричную строку
  stringstream ss;
  for (size_t i = 0; i < digest_len; i++) {
    // Форматирование: 2 hex-символа на байт с ведущими нулями
    ss << hex << setw(2) << setfill('0') << (int)digest[i];
  }

  OPENSSL_free(digest); // Освобождение памяти OpenSSL
  return ss.str();      // Возврат строки с хешем
}

int main() {
    // Пример использования: вычисление хеша для строки "Hello world!"
    std::cout << sha256("Hello world!") << '\n';
}