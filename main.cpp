#include <iostream>
#include <algorithm> // for std::max
#include <cmath>     // for std::ceil

template<typename T>
class DynamicSequenceContainer {
public:
    DynamicSequenceContainer() : m_data_ptr(nullptr) {
    }

    void push_back(T value) {
        increase_size_then_insert(m_data_size, value);
    }

    void insert(const size_t index, T value) {
        const size_t corrected_index = index > m_data_size ? m_data_size : index;
        increase_size_then_isnert(corrected_index, value);
    }


    void erase(const size_t index) {
        size_t optimal_min_size = static_cast<size_t>(std::floor(m_data_size / 1.5));

        T *new_region_ptr = new T[m_data_size - 1];
        for (size_t i = 0; i < index; ++i) {
            new_region_ptr[i] = m_data_ptr[i];
        }
        for (size_t i = index + 1; i < m_data_size; ++i) {
            new_region_ptr[i - 1] = m_data_ptr[i];
        }
        delete[] m_data_ptr;
        m_data_ptr = new_region_ptr;
        --m_data_size;
    }

    [[nodiscard]] size_t size() const {
        return m_data_size;
    }

    T &operator[](const size_t index) {
        return m_data_ptr[index];
    }

    const T &operator[](const size_t index) const {
        return m_data_ptr[index];
    }

private:
    T *m_data_ptr;
    size_t m_data_size{};
    size_t m_container_size{};


    void increase_size_then_insert(size_t const index, T const value) {
        // Push_back case AND container has empty space.
        if (index >= m_data_size and m_container_size > m_data_size) {
            // Do nothing. Exit.
            return;
        }

        // Calculate new container size. At least as long as 2 items.
        m_container_size = m_container_size < 2
                               ? 2
                               : static_cast<size_t>(std::ceil((m_data_size + 1) * 1.5));

        // Increase container up to new size
        T *new_region_ptr = new T[m_container_size];

        // Move data.
        if (index >= m_data_size) {
            // Push_back case
            for (size_t i = 0; i < m_data_size; ++i) {
                new_region_ptr[i] = m_data_ptr[i];
            }
        } else {
            // Insert case
            for (size_t i = 0; i < index; ++i) {
                new_region_ptr[i] = m_data_ptr[i];
            }
            for (size_t i = index; i < m_data_size; ++i) {
                new_region_ptr[i + 1] = m_data_ptr[i];
            }
        }

        delete[] m_data_ptr;
        m_data_ptr = new_region_ptr;

        m_data_ptr[index] = value;
        ++m_data_size;
    }

};

template<typename T>
struct Node {
    T data; // value
    Node *prev; // pointer to previous Node
    Node *next; // pointer to next Node
};

template<typename T>
class DynamicListContainer {
public:
    DynamicListContainer() : m_head(nullptr), m_tail(nullptr) {
    }

    void push_back(T value) {
        Node<T> *new_tail = new Node<T>{};
        new_tail->data = value;
        new_tail->next = nullptr;

        if (m_size) {
            // container has one or more items
            Node<T> *old_tail = m_tail;
            new_tail->prev = old_tail;
            old_tail->next = new_tail;
        } else {
            new_tail->prev = nullptr;
            m_head = new_tail;
        }
        m_tail = new_tail;
        ++m_size;
    }

    void insert(const size_t index, T value) {
        if (index >= m_size) {
            push_back(value);
            return;
        }
        Node<T> *old_node = get_node(index);
        Node<T> *previous_node = old_node->prev;
        Node<T> *new_node = new Node<T>{};

        new_node->data = value;
        new_node->prev = old_node->prev;
        new_node->next = old_node;

        if (index == 0) {
            m_head = new_node;
        } else {
            previous_node->next = new_node;
        }

        old_node->prev = new_node;

        ++m_size;
    }

    void erase(const size_t index) {
        if (m_size == 0 or index >= m_size) {
            return;
        }
        if (index == 0) {
            Node<T> *new_head = m_head->next;
            new_head->prev = nullptr;
            delete m_head;
            m_head = new_head;
        } else if (index == m_size - 1) {
            Node<T> *new_tail = m_tail->prev;
            new_tail->next = nullptr;
            delete m_tail;
            m_tail = new_tail;
        } else {
            Node<T> *node_to_be_removed = get_node(index);
            node_to_be_removed->prev->next = node_to_be_removed->next;
            node_to_be_removed->next->prev = node_to_be_removed->prev;
            delete node_to_be_removed;
        }
        --m_size;
    }

    [[nodiscard]] Node<T> *get_node(const size_t index) const {
        if (m_size == 0) {
            return nullptr;
        }
        if (index == 0) {
            // std::cout << "H";
            return m_head;
        }
        if (index >= m_size - 1) {
            // std::cout << "T";
            return m_tail;
        }
        const auto half_index = static_cast<size_t>(m_size / 2.0);
        if (m_size < 5 or index < half_index) {
            auto current_node = m_head;
            for (size_t i = 1; i <= index; ++i) {
                current_node = current_node->next;
            }
            // std::cout << "F(" << index << "-" << current_node << ")";
            return current_node;
        }
        auto current_node = m_tail;
        for (size_t i = m_size - 2; i >= index; --i) {
            current_node = current_node->prev;
        }
        // std::cout << "L(" << index << "-" << current_node << ")";
        return current_node;
    }

    T &operator[](const size_t index) {
        return get_node(index)->data;
    }

    const T &operator[](const size_t index) const {
        return get_node(index)->data;
    }

    [[nodiscard]] size_t size() const {
        return m_size;
    }

    [[nodiscard]] Node<T> *get_head() const {
        return m_head;
    }

private:
    size_t m_size{};
    Node<T> *m_head;
    Node<T> *m_tail;
};

template<typename T>
void disp_content(const T &container) {
    std::cout << "TEMPLATED:   ";
    const size_t c_size = container.size();

    if (c_size == 0) {
        std::cout << "(empty)" << std::endl;
        return;
    }
    for (size_t i = 0; i < c_size - 1; ++i) {
        std::cout << container[i] << ", ";
    }
    std::cout << container[c_size - 1] << std::endl;
}

// Partial specialization of disp_content for DynamicListContainer
template<typename T>
void disp_content(const DynamicListContainer<T> &container) {
    std::cout << "SPECIALIZED: ";
    const size_t c_size = container.size();

    if (c_size == 0) {
        std::cout << "(empty)" << std::endl;
        return;
    }

    Node<T> *current = container.get_head();

    for (size_t i = 0; i < c_size - 1; ++i) {
        std::cout << current->data << ", ";
        if (current->next) {
            current = current->next;
        } else {
            std::cout << "ERR" << std::endl;
            return;
        }
    }

    // Print the last element without a comma
    std::cout << current->data << std::endl;
}


template<typename T>
void container_test(T &container) {
    // 2. Add ten elements to the container (0, 1 ... 9)
    for (int i = 0; i < 10; ++i) {
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


int main() {
    std::cout << "Sequence container test:" << std::endl;
    DynamicSequenceContainer<int> s_container;
    container_test(s_container);

    std::cout << std::endl << "\nList container test:" << std::endl;
    DynamicListContainer<int> l_container;
    container_test(l_container);
}
