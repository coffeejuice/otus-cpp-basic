#include <iostream>
#include <algorithm> // for std::max
#include <cmath>     // for std::ceil

template <typename T>
class Sequence
{
public:
    class Iterator
    {
    public:
        explicit Iterator(T* ptr) : m_ptr(ptr)
        {
        }

        T& operator*() const { return *m_ptr; }
        [[nodiscard]] T& get() const { return *m_ptr; }

        // Pre-increment
        Iterator& operator++()
        {
            m_ptr++;
            return *this;
        }

        // Post-increment
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // Comparison operators
        friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }

    private:
        T* m_ptr;
    };

    // Iterator methods
    Iterator begin() { return Iterator(m_data_ptr); }
    Iterator end() { return Iterator(m_data_ptr + m_data_size); }

    // Const iterator methods
    const Iterator begin() const { return Iterator(m_data_ptr); }
    const Iterator end() const { return Iterator(m_data_ptr + m_data_size); }

    Sequence() : m_data_ptr(nullptr)
    {
    }

    // Add destructor to deallocate memory
    ~Sequence()
    {
        delete[] m_data_ptr;
    }

    // Copy
    Sequence(const Sequence& other) : Sequence{other.data()}
    {
    }

    // Move
    Sequence(const Sequence&& other) noexcept
    {
        // Check for self-assignment (unlikely but still good practice)
        if (this == &other)
            return;

        // Delete current resources
        delete[] m_data_ptr;

        // Move resources from other container
        m_data_ptr = other.m_data_ptr;
        m_data_size = other.m_data_size;
        m_container_size = other.m_container_size;

        // Reset other container to prevent double deletion
        other.m_data_ptr = nullptr;
        other.m_data_size = 0;
        other.m_container_size = 0;
    }

    // Copy assignment
    Sequence& operator=(const Sequence& other)
    {
        // Check for self-assignment
        if (this == &other)
            return *this;

        // Delete current resources
        delete[] m_data_ptr;

        // Copy size information
        m_data_size = other.m_data_size;
        m_container_size = other.m_container_size;

        // Allocate new memory
        if (m_container_size > 0)
        {
            m_data_ptr = new T[m_container_size];

            // Copy data from other container
            for (size_t i = 0; i < m_data_size; ++i)
            {
                m_data_ptr[i] = other.m_data_ptr[i];
            }
        }
        else
        {
            m_data_ptr = nullptr;
        }

        return *this;
    }

    // Move
    Sequence& operator=(Sequence&& other) noexcept
    {
        // Check for self-assignment (unlikely but still good practice)
        if (this == &other)
            return *this;

        // Delete current resources
        delete[] m_data_ptr;

        // Move resources from other container
        m_data_ptr = other.m_data_ptr;
        m_data_size = other.m_data_size;
        m_container_size = other.m_container_size;

        // Reset other container to prevent double deletion
        other.m_data_ptr = nullptr;
        other.m_data_size = 0;
        other.m_container_size = 0;

        return *this;
    }

    void push_back(T value)
    {
        // std::cout << "Push back " << value << " at index " << m_data_size << std::endl;
        insert(m_data_size, value);
    }

    void insert(const size_t input_index, T value)
    {
        // 'input_index' may exceed m_data_size. Limit 'input_index' by 'm_data_size'. Use 'index' as a limited one.
        const size_t index = input_index > m_data_size ? m_data_size : input_index;

        if (m_container_size > m_data_size)
        {
            // Container has empty space for a new value. Do not increase container.
            //
            // Move data to create a gap to insert a new value before moving items
            if (m_data_size > 0 and index < m_data_size)
            {
                for (size_t i = m_data_size; i > index; --i)
                {
                    m_data_ptr[i] = m_data_ptr[i - 1];
                }
            }
        }
        else
        {
            // Container needs to be increase in size before inserting a new value.
            //
            // Calculate a new container size. At least as long as 2 items.
            const size_t old_container_size = m_container_size;
            const size_t new_container_size = m_container_size < 2
                                                  ? 2
                                                  : static_cast<size_t>(std::ceil((m_data_size + 1) * 1.5));
            m_container_size = new_container_size > m_container_size ? new_container_size : m_container_size;

            std::cout << "Increase container size from " << old_container_size << " to " << m_container_size <<
                std::endl;

            // Increase container up to a new size
            T* new_region_ptr = new T[m_container_size];

            // Move data.
            for (size_t i = 0; i < index; ++i)
            {
                new_region_ptr[i] = m_data_ptr[i];
            }
            for (size_t i = index; i < m_data_size; ++i)
            {
                new_region_ptr[i + 1] = m_data_ptr[i];
            }

            delete[] m_data_ptr;
            m_data_ptr = new_region_ptr;
        }

        // Finally insert value
        m_data_ptr[index] = value;

        // Increase 'm_data_size'
        ++m_data_size;
    }


    void erase(const size_t index)
    {
        T* new_region_ptr = new T[m_data_size - 1];
        for (size_t i = 0; i < index; ++i)
        {
            new_region_ptr[i] = m_data_ptr[i];
        }
        for (size_t i = index + 1; i < m_data_size; ++i)
        {
            new_region_ptr[i - 1] = m_data_ptr[i];
        }
        delete[] m_data_ptr;
        m_data_ptr = new_region_ptr;
        --m_data_size;
    }

    [[nodiscard]] T* data() const { return m_data_ptr; }

    [[nodiscard]] size_t size() const { return m_data_size; }

    T& operator[](const size_t index) { return m_data_ptr[index]; }

    const T& operator[](const size_t index) const { return m_data_ptr[index]; }

    static const char* name() { return "DynamicSequenceContainer"; }

private:
    T* m_data_ptr;
    size_t m_data_size{};
    size_t m_container_size{};
};

// Base node template with a "next" pointer
template <typename T, typename NodeDerived>
struct NodeBase {
    T data;
    NodeDerived* next;
    
    NodeBase(T value) : data(value), next(nullptr) {}
};

// Single-linked node (essentially identical to base)
template <typename T>
struct Node1 : NodeBase<T, Node1<T>> {
    explicit Node1(T value) : NodeBase<T, Node1>(value) {}
};

// Double-linked node with additional prev pointer
template <typename T>
struct Node2 : NodeBase<T, Node2<T>> {
    Node2* prev;
    
    explicit Node2(T value) : NodeBase<T, Node2>(value), prev(nullptr) {}
};

template <typename T>
class ListBase {
public:
    class Iterator {
    public:
        explicit Iterator(NodeBase<T, Node2<T>>* ptr) : m_ptr(ptr) {}
        
        T& operator*() const { return m_ptr->data; }
        [[nodiscard]] T& get() const { return m_ptr->data; }
        
        // Pre-increment
        Iterator& operator++() {
            m_ptr = m_ptr->next;
            return *this;
        }

    protected:
        NodeBase<T, Node2<T>>* m_ptr;
    };
    
    // No longer need virtual for these methods!
    Iterator begin() { return Iterator(static_cast<NodeBase<T, Node2<T>>*>(m_head)); }
    Iterator end() { return Iterator(nullptr); }
    
    // Other methods that remain virtual...
    virtual void push_back(T value) = 0;
    virtual void insert(const size_t index, T value) = 0;
    // ...

protected:
    NodeBase<T, Node2<T>>* m_head{nullptr};
    NodeBase<T, Node2<T>>* m_tail{nullptr};
    size_t m_size{0};
};

template <typename T>
class List2 : public ListBase<T>
{
public:
    class Iterator : public ListBase<T>::Iterator
    {
    public:
        explicit Iterator(Node2<T>* ptr) : ListBase<T>::Iterator(ptr)
        {
        }
    };

    List2()
    {
    }

    List2& operator=(List2&& other) noexcept
    {
        // Check for self-assignment
        if (this == &other)
            return *this;

        // Clean up existing resources
        Node2<T>* current = static_cast<Node2<T>*>(this->m_head);
        while (current != nullptr)
        {
            Node2<T>* next = static_cast<Node2<T>*>(current->next);
            delete current;
            current = next;
        }

        // Move resources from other container
        this->m_head = other.m_head;
        this->m_tail = other.m_tail;
        this->m_size = other.m_size;

        // Reset other container to prevent double deletion
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;

        return *this;
    }

    void push_back(T value) override
    {
        auto* new_tail = new Node2<T>(value);

        if (this->m_size)
        {
            // a container has one or more items
            Node2<T>* old_tail = static_cast<Node2<T>*>(this->m_tail);
            new_tail->prev = old_tail;
            old_tail->next = new_tail;
        }
        else
        {
            new_tail->prev = nullptr;
            this->m_head = new_tail;
        }
        this->m_tail = new_tail;
        ++this->m_size;
    }

    void insert(const size_t index, T value) override
    {
        if (index >= this->m_size)
        {
            push_back(value);
            return;
        }
        Node2<T>* old_node = static_cast<Node2<T>*>(get_node(index));
        Node2<T>* previous_node = old_node->prev;
        Node2<T>* new_node = new Node2<T>(value);

        new_node->prev = old_node->prev;
        new_node->next = old_node;

        if (index == 0)
        {
            this->m_head = new_node;
        }
        else
        {
            previous_node->next = new_node;
        }

        old_node->prev = new_node;

        ++this->m_size;
    }

    void erase(const size_t index) override
    {
        if (this->m_size == 0 or index >= this->m_size)
        {
            return;
        }
        if (index == 0)
        {
            Node2<T>* new_head = static_cast<Node2<T>*>(this->m_head->next);
            new_head->prev = nullptr;
            delete this->m_head;
            this->m_head = new_head;
        }
        else if (index == this->m_size - 1)
        {
            Node2<T>* new_tail = static_cast<Node2<T>*>(this->m_tail->prev);
            new_tail->next = nullptr;
            delete this->m_tail;
            this->m_tail = new_tail;
        }
        else
        {
            Node2<T>* node_to_be_removed = static_cast<Node2<T>*>(get_node(index));
            node_to_be_removed->prev->next = node_to_be_removed->next;
            node_to_be_removed->next->prev = node_to_be_removed->prev;
            delete node_to_be_removed;
        }
        --this->m_size;
    }

    [[nodiscard]] NodeBase<T, Node2<T>>* get_node(const size_t index) const override
    {
        if (this->m_size == 0)
        {
            return nullptr;
        }
        if (index == 0)
        {
            // std::cout << "H";
            return this->m_head;
        }
        if (index >= this->m_size - 1)
        {
            // std::cout << "T";
            return this->m_tail;
        }
        const auto half_index = static_cast<size_t>(this->m_size / 2.0);
        if (this->m_size < 5 or index < half_index)
        {
            auto current_node = this->m_head;
            for (size_t i = 1; i <= index; ++i)
            {
                current_node = current_node->next;
            }
            // std::cout << "F(" << index << "-" << current_node << ")";
            return current_node;
        }
        auto current_node = this->m_tail;
        for (size_t i = this->m_size - 2; i >= index; --i)
        {
            current_node = current_node->prev;
        }
        // std::cout << "L(" << index << "-" << current_node << ")";
        return current_node;
    }

    T& operator[](const size_t index) override { return static_cast<Node2<T>*>(get_node(index))->data;}

    const T& operator[](const size_t index) const override { return static_cast<Node2<T>*>(get_node(index))->data;}

    static const char* name() { return "DynamicTwoWayListContainer";}
};

#include <string>

template <typename T>
class List1 : public ListBase<T>
{
public:
    class Iterator : public ListBase<T>::Iterator
    {
    public:
        explicit Iterator(Node1<T>* ptr) : ListBase<T>::Iterator(ptr)
        {
        }
    };

    List1()
    {
    }

    List1<T>& operator=(List1<T>&& other) noexcept
    {
        // Check for self-assignment
        if (this == &other)
            return *this;

        // Clean up existing resources
        Node1<T>* current = static_cast<Node1<T>*>(this->m_head);
        while (current != nullptr)
        {
            Node1<T>* next = static_cast<Node1<T>*>(current->next);
            delete current;
            current = next;
        }

        // Move resources from other container
        this->m_head = other.m_head;
        this->m_tail = other.m_tail;
        this->m_size = other.m_size;

        // Reset other container to prevent double deletion
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;

        return *this;
    }

    void push_back(T value) override
    {
        insert(this->m_size, value);
    }

    void insert(const size_t index, T value) override
    {
        auto* new_node = new Node1<T>(value);

        if (this->m_size == 0)
        {
            new_node->next = nullptr;
            this->m_head = new_node;
            this->m_tail = new_node;
        }
        else if (index == 0)
        {
            new_node->next = this->m_head;
            this->m_head = new_node;
        }
        else
        {
            // m_size > 0 and index > 0
            Node1<T>* previous_node = static_cast<Node1<T>*>(get_node(index - 1));
            Node1<T>* next_node = static_cast<Node1<T>*>(previous_node->next);
            previous_node->next = new_node;

            if (index >= this->m_size)
            {
                new_node->next = nullptr;
                this->m_tail = new_node;
            }
            else
            {
                new_node->next = next_node;
            }
        }
        ++this->m_size;
    }

    void erase(const size_t index) override
    {
        if (this->m_size == 0 or index >= this->m_size)
        {
            return;
        }

        if (index == 0)
        {
            Node1<T>* node_to_be_removed = static_cast<Node1<T>*>(this->m_head);
            this->m_head = this->m_head->next;
            delete node_to_be_removed;
        }
        else if (index == this->m_size - 1)
        {
            Node1<T>* previous_node = static_cast<Node1<T>*>(get_node(index - 1));
            Node1<T>* node_to_be_removed = static_cast<Node1<T>*>(previous_node->next);
            previous_node->next = nullptr;
            this->m_tail = previous_node;
            delete node_to_be_removed;
        }
        else
        {
            Node1<T>* previous_node = static_cast<Node1<T>*>(get_node(index - 1));
            Node1<T>* node_to_be_removed = static_cast<Node1<T>*>(previous_node->next);
            previous_node->next = node_to_be_removed->next;
            delete node_to_be_removed;
        }

        --this->m_size;
    }

    [[nodiscard]] NodeBase<T, Node2<T>>* get_node(const size_t index) const override
    {
        if (this->m_size == 0) return nullptr;
        if (index == 0) return this->m_head;
        if (index >= this->m_size - 1) return this->m_tail;

        auto current_node = this->m_head;
        for (size_t i = 1; i <= index; ++i)
        {
            current_node = current_node->next;
        }
        return current_node;
    }

    T& operator[](const size_t index) override { return static_cast<Node1<T>*>(get_node(index))->data;}

    const T& operator[](const size_t index) const override { return static_cast<Node1<T>*>(get_node(index))->data;}

    static const char* name() { return "DynamicSingleWayListContainer";}
};

template <typename T>
void disp_content(const T& container)
{
    std::cout << container.name() << ":   ";

    if (!container.size())
    {
        std::cout << "(empty)" << std::endl;
        return;
    }

    for (auto iter = container.begin(); iter != container.end(); ++iter)
    {
        std::cout << iter.get() << ", ";
    }
    std::cout << std::endl;
}

template <typename T>
void container_test(T& container)
{
    // 2. Add ten elements to the container (0, 1 ... 9)
    for (int i = 0; i < 10; ++i)
    {
        container.push_back(i);
    }

    // 3. Display the container contents on the screen
    //    Expected result: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    disp_content(container);

    // 4. Display the container size on the screen
    //    Expected result: 10
    std::cout << container.size() << std::endl;

    // 5. Remove the third, fifth, and seventh elements (by count)
    container.erase(6);
    container.erase(4);
    container.erase(2);

    // 6. Display the container contents on the screen
    //    Expected result: 0, 1, 3, 5, 7, 8, 9
    disp_content(container);

    // 7. Add element 10 to the beginning of the container
    container.insert(0, 10);

    // 8. Display the container contents on the screen
    //    Expected result: 10, 0, 1, 3, 5, 7, 8, 9
    disp_content(container);

    // 9. Add element 20 to the middle of the container
    int middle_index = static_cast<int>(container.size() / 2);
    container.insert(middle_index, 20);

    // 10. Display the container contents on the screen
    //     Expected result: 10, 0, 1, 3, 20, 5, 7, 8, 9
    disp_content(container);

    // 11. Add element 30 to the end of the container
    container.push_back(30);

    // 12. Display the container contents on the screen
    //     Expected result: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30
    disp_content(container);
}


int main()
{
    std::cout << "Sequence container test:" << std::endl;
    Sequence<int> s_container;
    container_test(s_container);

    std::cout << std::endl << "\nTwo-Way List container test:" << std::endl;
    List2<int> l_2_container;
    container_test(l_2_container);

    std::cout << std::endl << "\nSingle-Way List container test:" << std::endl;
    List1<int> l_1_container;
    container_test(l_1_container);
}