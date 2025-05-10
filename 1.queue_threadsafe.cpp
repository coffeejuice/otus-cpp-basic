#include <initializer_list>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

template <typename T>
struct Queue {
private:
    struct Node {
        Node() = default;
        Node(const T &value) : data{value} {}
        T data;
        std::unique_ptr<Node> next{nullptr};
    };

    std::unique_ptr<Node> m_head{nullptr};
    Node *m_tail{nullptr};
    mutable std::mutex m_mutex;

public:
    Queue() = default;
    Queue(const std::initializer_list<T> &values) {
        for (auto &v : values) {
            push(v);
        }
    }

    ~Queue() = default;

    void push(const T &value) {

        // Make new node - local work, no mutex required
        std::unique_ptr<Node> newNode = std::make_unique<Node>(value);
        Node *newTail = newNode.get();

        std::lock_guard lck{m_mutex};

        if (m_tail) {
            // If queue is not empy - just add to the end
            m_tail->next = std::move(newNode);
        } else {
            // If queue is empty, initialize new node as a head node
            m_head = std::move(newNode);
        }
        // Commit new tail
        m_tail = newTail;
    }

    bool empty() const {
        std::lock_guard lck{m_mutex};
        return !m_head;
    }

    bool pop(T &value) {
        // Error - deadlock here, because empty() method will lock the mutex again
        // std::lock_guard lck{m_mutex};

        // Check empty
        if (empty())
            return false;

        // Error - race condition here!

        {
            std::lock_guard lck{m_mutex};

            // Take value
            value = std::move(m_head->data);
            // Rewrite head to the next element
            m_head = std::move(m_head->next);
        }

        // Fix tail if the queue is empty now
        if(empty()) {
            m_tail = nullptr;
        }

        return true;
    }
};

// *************************************************************
void push_worker(Queue<int> &queue, int begin, int end) {
    for (int i = begin; i < end; ++i) {
        queue.push(i);
    }
}

void push_check() {
    std::cout << "push_check example" << std::endl;

    Queue<int> queue;

    const int count = 100'000;
    const int threadCount = 4;
    const int batchSize = count / threadCount;
    std::vector<std::thread> threads;
    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back(
            std::thread{push_worker, std::ref(queue), batchSize * i, std::min(batchSize * (i + 1), count)});
    }

    for (auto &thr : threads) {
        thr.join();
    }

    long long sum = 0;
    for (int value; queue.pop(value);) {
        sum += value;
    }

    long long expected = static_cast<long long>(count - 1) * count / 2;

    std::cout << "expected: " << expected << std::endl;
    std::cout << "actual: " << sum << std::endl << std::endl;
}

// *************************************************************
void pop_worker(Queue<int> &queue, int count, long long &sum) {
    for (int i = 0; i < count; ++i) {
        int value = 0;
        if (!queue.pop(value))
            break;
        sum += value;
    }
}

void pop_check() {
    std::cout << "pop_check example" << std::endl;

    Queue<int> queue;

    const int count = 100'000;
    const int threadCount = 4;
    const int batchSize = count / threadCount;

    for (int i = 0; i < count; ++i) {
        queue.push(i);
    }

    std::vector<long long> sums(threadCount, 0);
    std::vector<std::thread> threads;
    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back(
            std::thread{pop_worker, std::ref(queue), batchSize, std::ref(sums[i])});
    }

    for (auto &thr : threads) {
        thr.join();
    }

    long long sum = 0;
    for (auto &s : sums) {
        sum += s;
    }

    long long expected = static_cast<long long>(count - 1) * count / 2;

    std::cout << "expected: " << expected << std::endl;
    std::cout << "actual: " << sum << std::endl << std::endl;
}

int main() {
    push_check();
    pop_check();

    return 0;
}