#include <cstddef>
#include <string>
#include <iostream>

class String {
public:
    String(const char* cString): data{cString} { }
    std::size_t length() const {
        return data.size();
    }
private:
    std::string data;
};

// Не изменяем s в теле функции (вызываем только константные методы s)
void foo(const String& s) {
    std::cout << "string length " << s.length() << std::endl;
}

void base() {
    const String s("Hello!");
    foo(s); //ok
}

namespace text {
    class Surface{};

    class Text {
    public:
        void render(Surface& target) const {
            // здесь какая-то реализация отрисовки текста на target
            // состояние объекта Text меняться при отрисовке не должно
        }

        // set меняет состояние объекта. Значит, не константный
        void set(const std::string& text) {
            this->text = text;
        }

        // константный, не меняет text
        std::string get() const {
            return text;
        }
    private:
        std::string text;
    };

    // Отображает text на контексте s.
    // Если text пустой, вместо этого отображает строку "<none>"
    void show(const Text& text, Surface& s) {
        if (text.get().empty()) {
            Text tmp;
            tmp.set("<none>");
            tmp.render(s);
        } else {
            text.render(s);
        }
    }
}


int main() {
    base();
}