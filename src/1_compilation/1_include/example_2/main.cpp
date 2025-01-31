// Определение константы
#define PI 3.14159265

// Определение функции
#define MIN(x, y) x < y ? x : y

// Условная компиляция
#ifdef SETNUMBER
    #define NUMBER 42
#else
    #define NUMBER 21
#endif

int main()
{
    PI;
    auto result = MIN(1, 2);
    NUMBER;
}
