#pragma once

template <typename T>
struct Node1
{
    T data; // value
    Node1* next; // pointer to next Node
};

template <typename T>
class List1
{
public:
    class Iterator
    {
    public:
        explicit Iterator(Node1<T>* ptr) : m_ptr(ptr)
        {
        }

        T& operator*() const { return *m_ptr->data; }
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
        Node1<T>* m_ptr;
    };

    // Iterator methods
    Iterator begin() { return Iterator(m_head); }
    Iterator end() { return Iterator(nullptr); }

    // Const iterator methods
    Iterator begin() const { return Iterator(m_head); }
    Iterator end() const { return Iterator(nullptr); }

    // Destructor with memory deallocation
    ~List1()
    {
        Node1<T>* current = m_head;
        while (current != nullptr)
        {
            Node1<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    List1() : m_head(nullptr), m_tail(nullptr)
    {
    }

    // Copy constructor
    List1(const List1<T>& other) : m_head(nullptr), m_tail(nullptr)
    {
        // Copy resources from other container
        Node1<T>* other_current = other.m_head;
        while (other_current != nullptr)
        {
            push_back(other_current->data);  // Reuse existing push_back to maintain invariants
            other_current = other_current->next;
        }
    }

    // Move constructor
    List1(List1<T>&& other) noexcept : m_head(nullptr), m_tail(nullptr)
    {
        // Move resources from other container
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;

        // Reset other container to prevent double deletion
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    // Copy assignment
    List1<T>& operator=(const List1<T>& other)
    {
        // Check for self-assignment
        if (this == &other)
            return *this;

        // Clean up existing resources
        Node1<T>* current = m_head;
        while (current != nullptr)
        {
            Node1<T>* next = current->next;
            delete current;
            current = next;
        }

        // Reset our members
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;

        // Copy resources from other container
        Node1<T>* other_current = other.m_head;
        while (other_current != nullptr)
        {
            push_back(other_current->data);
            other_current = other_current->next;
        }

        return *this;
    }

    // Move assignment
    List1<T>& operator=(List1<T>&& other) noexcept
    {
        // Check for self-assignment
        if (this == &other)
            return *this;

        // Clean up existing resources
        Node1<T>* current = m_head;
        while (current != nullptr)
        {
            Node1<T>* next = current->next;
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
        insert(m_size, value);
    }

    void insert(const size_t index, T value)
    {
        auto* new_node = new Node1<T>{};
        new_node->data = value;

        if (m_size == 0)
        {
            new_node->next = nullptr;
            m_head = new_node;
            m_tail = new_node;
        }
        else if (index == 0)
        {
            new_node->next = m_head;
            m_head = new_node;
        }
        else
        {
            Node1<T>* previous_node = get_node(index - 1);
            Node1<T>* current_node = previous_node->next;
            
            previous_node->next = new_node;
            if (index >= m_size)
            {
                new_node->next = nullptr;
                m_tail = new_node;
            }
            else
            {
                new_node->next = current_node;
            }
        }
        ++m_size;
    }

    void erase(const size_t index)
    {
        if (m_size == 0 || index >= m_size)
        {
            return;
        }

        if (index == 0)
        {
            Node1<T>* node_to_be_removed = m_head;
            m_head = m_head->next;
            delete node_to_be_removed;
        }
        else
        {
            Node1<T>* previous_node = get_node(index - 1);
            Node1<T>* node_to_be_removed = previous_node->next;
            previous_node->next = node_to_be_removed->next;
            
            if (index == m_size - 1)
            {
                m_tail = previous_node;
            }
            
            delete node_to_be_removed;
        }

        --m_size;
    }

    [[nodiscard]] Node1<T>* get_node(const size_t index) const
    {
        if (m_size == 0) return nullptr;
        if (index == 0) return m_head;
        if (index >= m_size - 1) return m_tail;

        auto current_node = m_head;
        for (size_t i = 0; i < index; ++i)
        {
            current_node = current_node->next;
        }
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

    [[nodiscard]] Node1<T>* get_head() const
    {
        return m_head;
    }

    static const char* name()
    {
        return "Single linked List type container";
    }

private:
    size_t m_size{};
    Node1<T>* m_head;
    Node1<T>* m_tail;
};