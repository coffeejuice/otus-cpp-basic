#include "consumer.h"
#include <iostream>

namespace list {
    void work_consumer(WorkQueue& queue) {
        int value = 0;
        // make a waiting pop from the queue
        while (queue.pop(value)) {
            std::cout << "work_consumer - pop new value: " << value << std::endl;
        }
        std::cout << "work_consumer - end of cycle" << std::endl;
    }
}