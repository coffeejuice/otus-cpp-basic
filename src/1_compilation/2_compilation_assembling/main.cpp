// "U" The symbol is undefined.
void first_function(int);

// "T" The symbol is in the text (code) section.
void second_function(float)
{}

// "t" The symbol is in the text (code) section.
static void third_function(bool)
{}

int main()
{
    first_function(42);
    second_function(34.f);
    third_function(true);
}