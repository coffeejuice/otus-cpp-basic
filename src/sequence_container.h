#pragma once
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
    Iterator begin() const { return Iterator(m_data_ptr); }
    Iterator end() const { return Iterator(m_data_ptr + m_data_size); }

    // Destructor with memory deallocation
    ~Sequence()
    {
        delete[] m_data_ptr;
    }

    Sequence() : m_data_ptr(nullptr)
    {
    }

    // Copy constructor
    Sequence(const Sequence& other) : m_data_ptr(nullptr), m_data_size(other.m_data_size), m_container_size(other.m_container_size) {
        if (m_container_size > 0) {
            m_data_ptr = new T[m_container_size];
            for (size_t i = 0; i < m_data_size; ++i) {
                m_data_ptr[i] = other.m_data_ptr[i];
            }
        }
    }

    // Move constructor
    Sequence(Sequence&& other) noexcept :
        m_data_ptr(other.m_data_ptr),
        m_data_size(other.m_data_size),
        m_container_size(other.m_container_size)
    {
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

    // Move assignment
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

            std::cout << name() << ":   Increase container size from " << old_container_size << " to " << m_container_size <<
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

    static const char* name() { return "Sequence type container"; }

private:
    T* m_data_ptr;
    size_t m_data_size{};
    size_t m_container_size{};
};