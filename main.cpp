#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include "CRC32.hpp"
#include "IO.hpp"

#include <chrono>

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char>& data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char*>(&value), 4, data.end() - 4);
}

std::vector<char> do_injection(std::vector<char>& original,
                               const std::string& injection) {
  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);
  return result;
}

uint32_t crc32_split(const char* bytes, const size_t bytesCount,
                     const size_t percentage) {
  const size_t v_size = bytesCount * percentage / 100;
  if (v_size == 0) {
    return crc32(bytes, bytesCount);
  }
  const uint32_t v = crc32(bytes, v_size);
  return crc32(bytes + v_size, bytesCount - v_size, v);
}

void benchmark_crc32_split(const std::vector<char>& data) {
  const int iter_count = 100000; // Adjust based on your machine speed

  std::cout << "Data size: " << data.size() << " bytes\n";
  std::cout << "Percentage\tTime (ns)\n";
  for (size_t percentage = 0; percentage <= 95; percentage += 5) {
    auto start = std::chrono::high_resolution_clock::now();

    const uint32_t result = crc32_split(data.data(), data.size(), percentage);
    if (result == 0)
      std::cout << "."; // Prevent compiler from optimizing away the calculation
    for (int i = 0; i < (iter_count - 1); i++) {
      const auto next_result =
          crc32_split(data.data(), data.size(), percentage);
      if (next_result != result)
        throw std::logic_error("CRC32 mismatch");
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
        end - start);

    std::cout << percentage << "%\t\t" << static_cast<int>(
      duration.count() / iter_count) << "\n";
  }
}

/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @param percentage вычислить КС для первых percent исходного вектора для ускорения вычисления  CRC32
 * @return новый вектор
 */
std::vector<char> hack(std::vector<char>& original,
                       const std::string& injection, const size_t percentage) {
  const uint32_t originalCrc32 = crc32_split(original.data(), original.size(),
                                             percentage);
  std::vector<char> result = do_injection(original, injection);

  const size_t maxVal = std::numeric_limits<uint32_t>::max();
  const size_t print_increment = maxVal / 1000;

  for (size_t i = 0; i < maxVal; ++i) {
    // Заменяем последние четыре байта на значение i
    replaceLastFourBytes(result, uint32_t(i));
    // Вычисляем CRC32 текущего вектора result
    auto currentCrc32 = crc32_split(result.data(), result.size(), percentage);

    if (currentCrc32 == originalCrc32) {
      std::cout << "Success\n";
      return result;
    }
    // Отображаем прогресс
    if (i % print_increment == 0) {
      // Отображаем прогресс
      std::cout << "progress: "
          << static_cast<double>(i) / static_cast<double>(maxVal) * 100
          << "%\r" << std::flush;
      // Return caret to print all lines in same position
    }
  }
  throw std::logic_error("Can't hack");
}

int main(const int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Call with two args: " << argv[0]
        << " <input file> <output file>\n";
    return 1;
  }

  try {
    std::vector<char> data = readFromFile(argv[1]);

    // Test optimal split of CRC32 checksum calculation
    benchmark_crc32_split(data);
    // Split CRC32 checksum calculation on 20% by 80%
    const size_t percentage{20};

    const std::vector<char> badData = hack(data, "He-he-he", percentage);
    writeToFile(argv[2], badData);

    // Prevent terminal disappearing after calculations
    std::cout << "Press enter to exit\n";
    std::cin.get();
  } catch (std::exception& ex) {
    std::cerr << ex.what() << '\n';
    return 2;
  }
  return 0;
}