#include <algorithm>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <thread>
#include <vector>

#include "CRC32.hpp"
#include "IO.hpp"

// Constants
constexpr size_t DEFAULT_PERCENTAGE = 20;
constexpr int BENCHMARK_ITERATIONS = 100000;
constexpr size_t MULTI_THREADING_BENCHMARK_SAMPLE_SIZE_PERCENT = 1;

/**
 * @brief Replaces the last 4 bytes of data with the given value
 */
inline void
replaceLastFourBytes(std::vector<char>& data, const uint32_t value) {
  std::copy_n(reinterpret_cast<const char*>(&value), 4, data.end() - 4);
}

/**
 * @brief Creates a new vector by appending injection and 4 additional bytes to original
 */
std::vector<char> createInjectedVector(const std::vector<char>& original,
                                       const std::string& injection) {
  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);
  return result;
}

/**
 * @brief Calculates CRC32 with the data split at a given percentage
 */
uint32_t crc32_split(const char* bytes, const size_t bytesCount,
                     const size_t percentage) {
  const size_t splitPoint = bytesCount * percentage / 100;

  if (splitPoint == 0) {
    return crc32(bytes, bytesCount);
  }

  const uint32_t firstPartCrc = crc32(bytes, splitPoint);
  return crc32(bytes + splitPoint, bytesCount - splitPoint, firstPartCrc);
}

/**
 * @brief Benchmarks CRC32 split at various percentages
 */
void benchmarkCrc32Split(const std::vector<char>& data) {
  std::cout << "Data size: " << data.size() << " bytes\n";
  std::cout << "Percentage\tTime (ns)\n";

  for (size_t percentage = 0; percentage <= 95; percentage += 5) {
    auto start = std::chrono::high_resolution_clock::now();

    const uint32_t result = crc32_split(data.data(), data.size(), percentage);

    // Prevent compiler from optimizing away the calculation
    if (result == 0) {
      std::cout << ".";
    }

    for (int i = 0; i < (BENCHMARK_ITERATIONS - 1); i++) {
      const auto next_result =
          crc32_split(data.data(), data.size(), percentage);
      if (next_result != result) {
        throw std::logic_error("CRC32 mismatch");
      }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
        end - start);

    std::cout << percentage << "%\t\t"
        << static_cast<int>(duration.count() / BENCHMARK_ITERATIONS) << "\n";
  }
}

/**
 * @brief Worker function for bruteforce search in a specific range
 */
void worker(
    size_t start,
    size_t end,
    uint32_t targetCrc32,
    std::vector<char> result,
    std::atomic<bool>& found,
    std::shared_ptr<size_t> foundValue,
    const bool is_test = false
    ) {
  // size_t start{0};
  // size_t end{10000};
  for (size_t i = start; i < end + 1; ++i) {
    // Check if a solution already found by another thread
    if (found) {
      return;
    }
    // const uint32_t targetCrc32 = static_cast<uint32_t>(0);
    // std::vector<char> result({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',});
    replaceLastFourBytes(result, static_cast<uint32_t>(i));

    const uint32_t currentCrc32 = crc32_split(result.data(), result.size(),
                                              DEFAULT_PERCENTAGE);

    if (!is_test) {
      if (currentCrc32 == targetCrc32) {
        *foundValue = i;
        found = true;
        return;
      }
    }
  } // End for-cycle
}

std::vector<std::vector<size_t>> createThreadsRanges(
    const size_t threadCount, const bool is_test) {
  size_t maxVal;
  if (is_test) {
    maxVal = std::numeric_limits<uint32_t>::max() *
             MULTI_THREADING_BENCHMARK_SAMPLE_SIZE_PERCENT / 100;
  } else {
    maxVal = std::numeric_limits<uint32_t>::max();
  }

  // std::cout << "Threads count: " << threadCount << '\n';
  // std::cout << "Total range: 0 - " << maxVal << '\n';

  const size_t rangePerThread = maxVal / threadCount;

  // std::cout << "Thread # | Start range | End range" << std::endl;

  std::vector<std::vector<size_t>> ranges;
  for (size_t i = 0; i < threadCount; ++i) {
    const size_t start = i * rangePerThread;
    const size_t end = (i == threadCount - 1)
                         ? maxVal
                         : (i + 1) * rangePerThread - 1;

    // std::cout << "#" << i << " 0x" << std::hex << std::setw(8) <<
    //     std::setfill('0')
    //     << start << " - 0x" << std::setw(8) << std::setfill('0')
    //     << end << std::dec << std::endl;
    ranges.emplace_back(std::vector<size_t>{start, end});
  }
  return ranges;
}


/**
 * @brief Creates a new vector with the same CRC32 by adding injection and 4 bytes
 *
 * This function adds the injection data to the original vector and then finds
 * a 4-byte value to append that makes the CRC32 match the original.
 *
 * @param original Origal data vector
 * @param injection String to inject after original data
 * @param percentage Percentage for CRC32 split calculation
 * @return Modified vector with matching CRC32
 */
std::vector<char> hack(
    const std::vector<char>& original,
    const std::string& injection,
    const size_t threadCount,
    const bool is_test
    ) {
  const uint32_t targetCrc32 = crc32_split(original.data(), original.size(),
                                           DEFAULT_PERCENTAGE);
  if (!is_test)
    std::cout << "Original CRC32: " << targetCrc32 << '\n';

  std::vector<std::vector<size_t>> ranges = createThreadsRanges(
      threadCount, is_test);

  // Prepare result storage for each thread
  std::vector<std::shared_ptr<size_t>> foundValues;
  foundValues.reserve(threadCount);
  for (size_t i = 0; i < threadCount; ++i) {
    foundValues.emplace_back(std::make_shared<size_t>(0));
  }

  std::atomic<bool> found{false};
  std::vector<char> result = createInjectedVector(original, injection);

  // Launch worker threads
  std::vector<std::thread> threads;
  threads.reserve(threadCount);

  for (size_t i = 0; i < threadCount; ++i) {
    // size_t start = ranges[i][0];
    // size_t end = ranges[i][1];
    std::thread th(
        worker,
        ranges[i][0],
        ranges[i][1],
        targetCrc32,
        result,
        std::ref(found),
        foundValues[i],
        is_test
        );
    threads.emplace_back(std::move(th));
  }

  if (!is_test)
    std::cout << "\nAll threads started. Waiting for threads to finish..." <<
        std::endl;

  // Join all threads
  for (auto& thread : threads) {
    thread.join();
  }

  // std::cout << "\nAll threads finished" << std::endl;

  if (is_test) {
    return result;
  }

  if (found) {
    // Find the thread that found the value and use its result
    for (size_t i = 0; i < threadCount; ++i) {
      if (*foundValues[i] > 0) {
        std::cout << "Thread #" << i << " found value: " << *foundValues[i] <<
            std::endl;
        replaceLastFourBytes(result, static_cast<uint32_t>(*foundValues[i]));
        return result;
      }
    }
  }

  throw std::logic_error("Failed to find matching CRC32 value");
}


size_t benchmarkMultiThreading(const std::vector<char>& original,
                               const std::string& injection) {
  // Set up benchmark parameters
  const auto maxThreadCount = std::thread::hardware_concurrency();

  // Generate thread counts to test (powers of 2 up to maxThreadCount)
  std::vector<size_t> threadCounts;
  for (size_t count = 1; count < maxThreadCount; count *= 2) {
    threadCounts.push_back(count);
  }

  // Add maximum thread count if not already included
  if (threadCounts.back() != maxThreadCount) {
    threadCounts.push_back(maxThreadCount);
  }

  // Store benchmark results
  std::vector<double> durations(threadCounts.size());

  // Run benchmark for each thread count
  for (size_t i = 0; i < threadCounts.size(); ++i) {
    size_t currentThreadCount = threadCounts[i];

    // Timing start
    auto startTime = std::chrono::high_resolution_clock::now();

    const std::vector<char> modifiedData = hack(original, injection,
                                                currentThreadCount, true);

    // Measure elapsed time
    auto endTime = std::chrono::high_resolution_clock::now();
    const long long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
        endTime - startTime).count();

    // const auto dur = static_cast<double>(milliseconds) / 1000.0;
    durations[i] = static_cast<double>(milliseconds) / 1000.0;
    // Store the raw milliseconds for later calculations

    // Set precision for output
    std::cout << "Threads count: " << currentThreadCount
        << " Time: " << std::fixed << std::setprecision(2) << durations[i] << " s" <<
        std::endl;
  }

  // Find optimal thread count (minimum duration)
  auto minDurationIt = std::min_element(durations.begin(), durations.end());
  auto optimalIndex = static_cast<size_t>(std::distance(
      durations.begin(), minDurationIt));
  size_t optimalThreadCount = threadCounts[optimalIndex];

  std::cout << "Optimal threads count: " << optimalThreadCount
      << " with time: " << std::setprecision(2) << *minDurationIt  << " s" << std::endl;

  return optimalThreadCount;
}


int main(const int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
    return 1;
  }

  try {
    std::vector<char> data = readFromFile(argv[1]);

    // Test optimal split of CRC32 checksum calculation
    std::cout << "\n## BENCHMARK: CRC32 split claculation ##\n";
    benchmarkCrc32Split(data);

    // Test multi-threading
    std::cout << "\n## BENCHMARK: Find optimal number of threads ##\n";
    const size_t optimalThreadCount = benchmarkMultiThreading(data, "He-he-he");

    // Split CRC32 checksum calculation at 20%/80%
    std::cout << "\n## MAIN TASK: Multi-threaded CRC32 hack ##\n";
    const std::vector<char> modifiedData = hack(data, "He-he-he",
                                                optimalThreadCount, false);
    writeToFile(argv[2], modifiedData);

    // Prevent terminal from closing immediately
    std::cout << "Press enter to exit [Enter]:\n";
    std::cin.get();
  } catch (const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << '\n';
    return 2;
  }

  return 0;
}