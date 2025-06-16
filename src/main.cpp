#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>
#include "queue.h"
#include "producer.h"
#include "consumer.h"

namespace list {
    void main_func() {
        std::atomic<bool> stop_flag = false;
        WorkQueue work_queue;

        std::cout << "Launch threads!" << std::endl;

        std::thread work_producer_thread{work_producer, std::ref(work_queue), std::ref(stop_flag)};
        std::thread work_consumer_thread1{work_consumer, std::ref(work_queue)};
        std::thread work_consumer_thread2{work_consumer, std::ref(work_queue)};

        std::this_thread::sleep_for(std::chrono::seconds{5});

        std::cout << "Finish working!" << std::endl;

        // stop all threads
        stop_flag = true;
        // need this to unblock all threads, which are waiting the queue
        work_queue.stop();
        // wait all threads
        work_producer_thread.join();
        work_consumer_thread1.join();
        work_consumer_thread2.join();

        std::cout << "Finished!" << std::endl;
    }
} // namespace list

int main() { list::main_func(); }