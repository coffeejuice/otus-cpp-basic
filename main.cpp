#include <iostream>
#include "sequence_container.h"
#include "double_linked_list_contaner.h"
#include "single_linked_list_container.h"


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
    std::cout << container.name() << ":   Add ten elements to the container (0, 1 ... 9)" << std::endl;
    for (int i = 0; i < 10; ++i)
    {
        container.push_back(i);
    }

    // 3. Display the container contents on the screen
    //    Expected result: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    disp_content(container);

    // 4. Display the container size on the screen
    //    Expected result: 10
    std::cout << container.name() << ":   Container size = " << container.size() << std::endl;

    // 5. Remove the third, fifth, and seventh elements (by count)
    std::cout << container.name() << ":   Remove the third, fifth, and seventh elements (by count)" << std::endl;
    container.erase(6);
    container.erase(4);
    container.erase(2);

    // 6. Display the container contents on the screen
    //    Expected result: 0, 1, 3, 5, 7, 8, 9
    disp_content(container);

    // 7. Add element 10 to the beginning of the container
    std::cout << container.name() << ":   Add element 10 to the beginning of the container" << std::endl;
    container.insert(0, 10);

    // 8. Display the container contents on the screen
    //    Expected result: 10, 0, 1, 3, 5, 7, 8, 9
    disp_content(container);

    // 9. Add element 20 to the middle of the container
    std::cout << container.name() << ":   Add element 20 to the middle of the container" << std::endl;
    int middle_index = static_cast<int>(container.size() / 2);
    container.insert(middle_index, 20);

    // 10. Display the container contents on the screen
    //     Expected result: 10, 0, 1, 3, 20, 5, 7, 8, 9
    disp_content(container);

    // 11. Add element 30 to the end of the container
    std::cout << container.name() << ":   Add element 30 to the end of the container" << std::endl;
    container.push_back(30);

    // 12. Display the container contents on the screen
    //     Expected result: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30
    disp_content(container);
}


int main()
{
    std::cout << "\nSequence container test:" << std::endl;
    Sequence<int> s_container;
    container_test(s_container);

    std::cout << std::endl << "\nDouble linked List container test:" << std::endl;
    List2<int> l_2_container;
    container_test(l_2_container);

    std::cout << std::endl << "\nSingle linked List container test:" << std::endl;
    List1<int> l_1_container;
    container_test(l_1_container);
}