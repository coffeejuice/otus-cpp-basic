#include <cstddef>
#include <cstring>

/**
 * @warning строка ссылается на данные, которые передали в конструкторе,
 * не владеет ими (не делает копию)
 */
class String {
public:
    std::size_t length() const {
        // Если закешированная длина неактуальна, вычисляем ее и кешируем
        // Благодаря mutable меняем поля в константном методе
        if (!cacheIsActual) {
            cachedLength = strlen(cStyleStr);
            cacheIsActual = true;
        }
        return cachedLength;
    }

    void set(const char* cStyleStr) {
        // если задали новую строку, сохраняем указатель на нее
        this->cStyleStr = cStyleStr;
        // и сбрасываем признак того, что закешированная длина актуальна
        cacheIsActual = false;
    }

private:
    const char *cStyleStr = nullptr;
    // Объявляем поля мутабельными. Это позволяет менять их в константных методах
    mutable std::size_t cachedLength = 0;
    mutable bool cacheIsActual = true;
};

int main() {}
