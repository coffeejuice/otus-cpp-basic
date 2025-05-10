#include <initializer_list>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


template <typename T>
struct Queue {
private:
    struct Node {
        Node() = default;
        Node(const T& value) : data{value} {}
        T data;
        std::unique_ptr<Node> next{nullptr};
    };

    std::unique_ptr<Node> m_head{nullptr};
    Node* m_tail{nullptr};

public:
    Queue() = default;
    Queue(const std::initializer_list<T>& values) {
        for(auto& v : values) {
            push(v);
        }
    }

    ~Queue() = default;

    void push(const T& value) {

        // Make new node
        std::unique_ptr<Node> newNode = std::make_unique<Node>( value );
        Node *newTail = newNode.get();

        if(m_tail) {
            // If queue is not empy - just add to the end
            m_tail->next = std::move( newNode );
        } else {
            // If queue is empty, initialize new node as a head node
            m_head = std::move( newNode );
        }
        // Commit new tail
        m_tail = newTail;

    }

    bool empty() const {
        return !m_head;
    }

    bool pop(T& value) {
        // Check empty
        if (empty()) return false;

        // Take value
        value = std::move(m_head->data);
        // Rewrite head to the next element
        m_head = std::move(m_head->next);

        return true;
    }


};

int main() {
    Queue<std::string> queue;

    std::vector<std::string> strings{
        "Hello",
        "from",
        "an",
        "example",
        "of",
        "using",
        "a",
        "non-thread-safe",
        "queue!"
    };

    for(auto& s : strings) {
        queue.push(s);
    }

    for(std::string str; queue.pop(str); ) {
        std::cout << str << std::endl;
    }

    return 0;
}