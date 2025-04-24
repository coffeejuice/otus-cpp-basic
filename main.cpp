#include <iostream>
#include <algorithm> // for std::max
#include <cmath>     // for std::ceil

template <typename T>
class DynamicSequenceContainer
{
public:
    DynamicSequenceContainer() : m_data_ptr(nullptr)
    {
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

    [[nodiscard]] size_t size() const
    {
        return m_data_size;
    }

    T& operator[](const size_t index)
    {
        return m_data_ptr[index];
    }

    const T& operator[](const size_t index) const
    {
        return m_data_ptr[index];
    }

    static const char* name()
    {
        return "DynamicSequenceContainer";
    }

private:
    T* m_data_ptr;
    size_t m_data_size{};
    size_t m_container_size{};
};

template <typename T>
struct NodeTwoWay
{
    T data; // value
    NodeTwoWay* prev; // pointer to previous Node
    NodeTwoWay* next; // pointer to next Node
};

template <typename T>
struct NodeSingleWay
{
    T data; // value
    NodeSingleWay* next; // pointer to next Node
};

template <typename T>
class DynamicTwoWayListContainer
{
public:
    DynamicTwoWayListContainer() : m_head(nullptr), m_tail(nullptr)
    {
    }

    void push_back(T value)
    {
        auto* new_tail = new NodeTwoWay<T>{};
        new_tail->data = value;
        new_tail->next = nullptr;

        if (m_size)
        {
            // a container has one or more items
            NodeTwoWay<T>* old_tail = m_tail;
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
        NodeTwoWay<T>* old_node = get_node(index);
        NodeTwoWay<T>* previous_node = old_node->prev;
        NodeTwoWay<T>* new_node = new NodeTwoWay<T>{};

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
        if (m_size == 0 or index >= m_size)
        {
            return;
        }
        if (index == 0)
        {
            NodeTwoWay<T>* new_head = m_head->next;
            new_head->prev = nullptr;
            delete m_head;
            m_head = new_head;
        }
        else if (index == m_size - 1)
        {
            NodeTwoWay<T>* new_tail = m_tail->prev;
            new_tail->next = nullptr;
            delete m_tail;
            m_tail = new_tail;
        }
        else
        {
            NodeTwoWay<T>* node_to_be_removed = get_node(index);
            node_to_be_removed->prev->next = node_to_be_removed->next;
            node_to_be_removed->next->prev = node_to_be_removed->prev;
            delete node_to_be_removed;
        }
        --m_size;
    }

    [[nodiscard]] NodeTwoWay<T>* get_node(const size_t index) const
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

    [[nodiscard]] NodeTwoWay<T>* get_head() const
    {
        return m_head;
    }

    static const char* name()
    {
        return "DynamicTwoWayListContainer";
    }

private:
    size_t m_size{};
    NodeTwoWay<T>* m_head;
    NodeTwoWay<T>* m_tail;
};

#include <string>

template <typename T>
class DynamicSingleWayListContainer
{
public:
    DynamicSingleWayListContainer() : m_head(nullptr), m_tail(nullptr)
    {
    }

    void push_back(T value)
    {
        insert(m_size, value);
    }

    void insert(const size_t index, T value)
    {
        auto* new_node = new NodeSingleWay<T>{};
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
            // m_size > 0 and index > 0
            NodeSingleWay<T>* previous_node = get_node(index - 1);
            NodeSingleWay<T>* current_node = previous_node->next;
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
        if (m_size == 0 or index >= m_size)
        {
            return;
        }

        NodeSingleWay<T>* previous_node = get_node(index - 1);

        if (index == m_size - 1)
        {
            previous_node->next = nullptr;
            delete m_tail;
            m_tail = previous_node;
        }

        NodeSingleWay<T>* next_node = get_node(index + 1);

        if (index == 0)
        {
            NodeSingleWay<T>* new_head = m_head->next;
            delete m_head;
            m_head = new_head;
        }
        else
        {
            NodeSingleWay<T>* node_to_be_removed = next_node->prev;
            next_node->prev = node_to_be_removed->prev;
            delete node_to_be_removed;
        }
        --m_size;
    }

    [[nodiscard]] NodeSingleWay<T>* get_node(const size_t index) const
    {
        if (m_size == 0) return nullptr;
        if (index == 0) return m_head;
        if (index >= m_size - 1) return m_tail;

        auto current_node = m_tail;
        for (size_t i = m_size - 2; i >= index; --i)
        {
            current_node = current_node->prev;
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

    [[nodiscard]] NodeSingleWay<T>* get_head() const
    {
        return m_head;
    }

    static const char* name()
    {
        return "DynamicSingleWayListContainer";
    }

private:
    size_t m_size{};
    NodeSingleWay<T>* m_head;
    NodeSingleWay<T>* m_tail;
};

template <typename T>
void disp_content(const T& container)
{
    std::cout << container.name() << ":   ";
    const size_t c_size = container.size();

    if (c_size == 0)
    {
        std::cout << "(empty)" << std::endl;
        return;
    }
    for (size_t i = 0; i < c_size - 1; ++i)
    {
        std::cout << container[i] << ", ";
    }
    std::cout << container[c_size - 1] << std::endl;
}

// Partial specialization of disp_content for DynamicListContainer
template <typename T>
void disp_content(const DynamicTwoWayListContainer<T>& container)
{
    std::cout << container.name() << ": ";
    const size_t c_size = container.size();

    if (c_size == 0)
    {
        std::cout << "(empty)" << std::endl;
        return;
    }

    NodeTwoWay<T>* current = container.get_head();

    for (size_t i = 0; i < c_size - 1; ++i)
    {
        std::cout << current->data << ", ";
        if (current->next)
        {
            current = current->next;
        }
        else
        {
            std::cout << "ERR" << std::endl;
            return;
        }
    }

    // Print the last element without a comma
    std::cout << current->data << std::endl;
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
    DynamicSequenceContainer<int> s_container;
    container_test(s_container);

    std::cout << std::endl << "\nTwo-Way List container test:" << std::endl;
    DynamicTwoWayListContainer<int> l_2_container;
    container_test(l_2_container);

    std::cout << std::endl << "\nSingle-Way List container test:" << std::endl;
    DynamicSingleWayListContainer<int> l_1_container;
    container_test(l_1_container);
}
