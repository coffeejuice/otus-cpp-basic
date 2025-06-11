#include <atomic>
#include <iostream>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>
constexpr static int productsCount = 1000;

namespace heater {
    class Queue {
    public:
        void push(int v) {
            std::lock_guard _{m};
            q.push(v);
        }
        std::optional<int> pop() {
            std::lock_guard _{m};
            if (!q.empty()) {
                int result = q.front();
                q.pop();
                return result;
            }
            return std::nullopt;
        }
    private:
        std::mutex m;
        std::queue<int> q;
    };

    void example() {
        Queue queue;
        std::atomic_bool stopped{};
        int total{};

        auto producer = std::thread([&]() {
            for (int i = 0; i < productsCount; ++i) {
                queue.push(i);
            }
            stopped = true;
        });

        auto consumer = std::thread([&]() {
            std::optional<int> value;
            bool finished{};
            while (!finished) {
                if (stopped) {
                    finished = true;
                }

                value = queue.pop();
                total += value.value_or(0);

                if (value) {
                    finished = false;
                } else {
                    using namespace std::chrono_literals;
                    std::this_thread::sleep_for(1ms);
                }
            }
        });
        producer.join();
        consumer.join();
        std::cout << total << std::endl;
        std::cout << productsCount * (productsCount - 1) / 2 << std::endl;
    }
} // namespace heater

int main() { heater::example(); }