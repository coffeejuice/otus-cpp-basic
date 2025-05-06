

int main() {

    {
        auto ptr = new int{10};
        int* ptr2 = ptr;
        // ...
        delete ptr2;
        delete ptr;
    }

    {
        auto value = 10;
        int* ptr = new int{10};
        int* ptr2 = ptr;

        // ...
        
        ptr = &value;
    }

    {
        int* ptr = new int[10];

        // ...

        delete[] ptr;
    }

    {
        auto ptr = new int[10];

        // if (...) {
            
        // } else if (...) {
        //     ...
        // } else if (...) {
        // 
        //     return ... !!!!!!!
        // } ...

        delete[] ptr;
    }

    return 0;
}
