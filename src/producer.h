#pragma once
#include <atomic>
#include <windows.h>
#include <algorithm>
#include <iostream>
#include "queue.h"

namespace list {
    void work_producer(WorkQueue& queue, std::atomic<bool>& stop_flag);
}