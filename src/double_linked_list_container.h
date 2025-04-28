#pragma once

template <typename T>
struct Node2
{
    T data;
    Node2* prev;
    Node2* next;
    
    Node2() : data(), prev(nullptr), next(nullptr) {}
    explicit Node2(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class List2
{
public:
    class Iterator
    {
    public:
        explicit Iterator(Node2<T>* ptr) : m_ptr(ptr)
        {
        }

        T& operator*() const { return m_ptr->data; }
        [[nodiscard]] T& get() const { return m_ptr->data; }

        // Pre-increment
        Iterator& operator++()
        {
            m_ptr = m_ptr->next;
            return *this;
        }

        // Post-increment
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            m_ptr = m_ptr->next;
            return tmp;
        }

        // Comparison operators
        friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }

    private:
        Node2<T>* m_ptr;
    };

    // Iterator methods
    Iterator begin() { return Iterator(m_head); }
    Iterator end() { return Iterator(nullptr); }

    // Const iterator methods
    Iterator begin() const { return Iterator(m_head); }
    Iterator end() const { return Iterator(nullptr); }

    // Destructor with memory deallocation
    ~List2()
    {
        Node2<T>* current = m_head;
        while (current != nullptr)
        {
            Node2<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    List2() : m_head(nullptr), m_tail(nullptr)
    {
    }

    // Copy constructor
    List2(const List2<T>& other) : m_head(nullptr), m_tail(nullptr)
    {
        // Copy resources from other container
        Node2<T>* other_current = other.m_head;
        while (other_current != nullptr)
        {
            push_back(other_current->data);  // Reuse existing push_back to maintain invariants
            other_current = other_current->next;
        }
    }

    // Move constructor
    List2(List2<T>&& other) noexcept : m_size(other.m_size), m_head(other.m_head), m_tail(other.m_tail)
    {
        // Reset other container to prevent double deletion
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    // Copy assignment
    List2<T>& operator=(const List2<T>& other) noexcept
    {
        // Check for self-assignment
        if (this == &other)
            return *this;

        // Clean up existing resources
        Node2<T>* current = m_head;
        while (current != nullptr)
        {
            Node2<T>* next = current->next;
            delete current;
            current = next;
        }

        // Copy resources from other container
        Node2<T>* other_current = other.m_head;
        while (other_current != nullptr)
        {
            push_back(other_current->data);  // Reuse existing push_back to maintain invariants
            other_current = other_current->next;
        }

        return *this;
    }

    // Move assignment
    List2<T>& operator=(List2<T>&& other) noexcept
    {
        // Check for self-assignment
        if (this == &other)
            return *this;

        // Clean up existing resources
        Node2<T>* current = m_head;
        while (current != nullptr)
        {
            Node2<T>* next = current->next;
            delete current;
            current = next;
        }

        // Move resources from other container
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;

        // Reset other container to prevent double deletion
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;

        return *this;
    }

    void push_back(T value)
    {
        auto* new_tail = new Node2<T>{};
        new_tail->data = value;
        new_tail->next = nullptr;

        if (m_size)
        {
            // a container has one or more items
            Node2<T>* old_tail = m_tail;
            new_tail->prev = old_tail;
            old_tail->next = new_tail;
        }
        else
        {
            new_tail->prev = nullptr;
            m_head = new_tail;
        }
        m_tail = new_tail;
        ++m_size;
    }

    void insert(const size_t index, T value)
    {
        if (index >= m_size)
        {
            push_back(value);
            return;
        }
        Node2<T>* old_node = get_node(index);
        Node2<T>* previous_node = old_node->prev;
        Node2<T>* new_node = new Node2<T>{};

        new_node->data = value;
        new_node->prev = old_node->prev;
        new_node->next = old_node;

        if (index == 0)
        {
            m_head = new_node;
        }
        else
        {
            previous_node->next = new_node;
        }

        old_node->prev = new_node;

        ++m_size;
    }

    void erase(const size_t index)
    {
        if (m_size == 0 || index >= m_size)
        {
            return;
        }

        if (m_size == 1)
        {
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
            m_size = 0;
            return;
        }

        if (index == 0)
        {
            Node2<T>* new_head = m_head->next;
            if (new_head)
            {
                new_head->prev = nullptr;
            }
            delete m_head;
            m_head = new_head;
        }
        else if (index == m_size - 1)
        {
            Node2<T>* new_tail = m_tail->prev;
            if (new_tail)
            {
                new_tail->next = nullptr;
            }
            delete m_tail;
            m_tail = new_tail;
        }
        else
        {
            Node2<T>* node_to_be_removed = get_node(index);
            if (node_to_be_removed->prev)
            {
                node_to_be_removed->prev->next = node_to_be_removed->next;
            }
            if (node_to_be_removed->next)
            {
                node_to_be_removed->next->prev = node_to_be_removed->prev;
            }
            delete node_to_be_removed;

        }
        --m_size;
    }

    void clear()
    {
        Node2<T>* current = m_head;
        while (current != nullptr)
        {
            Node2<T>* next = current->next;
            delete current;
            current = next;
        }
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    }

    [[nodiscard]] Node2<T>* get_node(const size_t index) const
    {
        if (m_size == 0)
        {
            return nullptr;
        }
        if (index == 0)
        {
            // std::cout << "H";
            return m_head;
        }
        if (index >= m_size - 1)
        {
            // std::cout << "T";
            return m_tail;
        }
        const auto half_index = static_cast<size_t>(m_size / 2.0);
        if (m_size < 5 or index < half_index)
        {
            auto current_node = m_head;
            for (size_t i = 1; i <= index; ++i)
            {
                current_node = current_node->next;
            }
            // std::cout << "F(" << index << "-" << current_node << ")";
            return current_node;
        }
        auto current_node = m_tail;
        for (size_t i = m_size - 2; i >= index; --i)
        {
            current_node = current_node->prev;
        }
        // std::cout << "L(" << index << "-" << current_node << ")";
        return current_node;
    }

    T& operator[](const size_t index)
    {
        return get_node(index)->data;
    }

    const T& operator[](const size_t index) const
    {
        return get_node(index)->data;
    }

    [[nodiscard]] size_t size() const
    {
        return m_size;
    }

    [[nodiscard]] Node2<T>* get_head() const
    {
        return m_head;
    }

    static const char* name()
    {
        return "Double linked List type container";
    }

private:
    size_t m_size{};
    Node2<T>* m_head;
    Node2<T>* m_tail;
};