#pragma once
#include <condition_variable>
#include <memory>
#include <mutex>
#include <iostream>

namespace list {
        // Mutex + pointer
    template <typename T>
    struct WithMutex {
        template <class TT>
        explicit WithMutex(TT&& ptr) : ptr{std::forward<TT>(ptr)} {
        }

        T ptr;
        std::mutex mutex;
    };

    template <typename T>
    struct WaitingQueue {

        WaitingQueue() : head{new Node}, tail{head.ptr.get()}, m_stopped{false} {
        }

        /** @brief Takes entry with waiting is a case of empty queue.
         *  @param entry result entry.
         *  @note This is a blocking function!
         *  @return false in case of an empty stopped queue
         */
        bool pop(T& entry) {
            std::unique_lock lck{head.mutex};
            m_conditional.wait(lck, [this]() { return m_stopped || head.ptr.get() != getTailSafe(); });

            if (m_stopped)
                return false;
            // Take value
            entry = std::move(head.ptr->value);
            // And remove the head node from the list
            takeHeadUnsafe();
            return true;
        }

        /** @brief Try to take entry without waiting
         *  @param entry result entry.
         *  @return false in case of an empty queue
         */
        bool tryPop(T& entry) {
            std::lock_guard<std::mutex> lck{head.mutex};
            if (head.get() == getTailSafe()) {
                // WaitingQueue is empty
                return false;
            }
            // Take value from the head node.
            entry = std::move(head.ptr->value);
            // And remove the head node from the list.
            std::unique_ptr<Node> prevHead = takeHeadUnsafe();
            return prevHead.get() != nullptr;
        }

        template <typename TT>
        void push(TT&& value) {
            std::lock_guard<std::mutex> lck{tail.mutex};

            if (!m_stopped) {
                tail.ptr->value = std::forward<TT>(value);
                tail.ptr->next.reset(new Node);
                tail.ptr = tail.ptr->next.get();
                m_conditional.notify_one();
            }
        }

        /// @brief Notify all threads to unblock them.
        void stop() {
            std::scoped_lock lock(head.mutex, tail.mutex);
            std::cout << "Set m_stopped to True" << std::endl;
            m_stopped = true;
            m_conditional.notify_all();
        }

    private:
        struct Node {
            T value;
            std::unique_ptr<Node> next;
        };

        Node* getTailSafe() {
            std::lock_guard<std::mutex> lck{tail.mutex};
            return tail.ptr;
        }

        std::unique_ptr<Node> takeHeadUnsafe() {
            std::unique_ptr<Node> prevHead = std::move(head.ptr);
            head.ptr = std::move(prevHead->next);
            return prevHead;
        }

        // head element of the WaitingQueue
        WithMutex<std::unique_ptr<Node>> head;
        // pointer to the tail element
        WithMutex<Node*> tail;
        // Condition for waiting data
        std::condition_variable m_conditional;
        // Stop flag
        bool m_stopped;
    };

    using WorkQueue = WaitingQueue<std::string>;
}