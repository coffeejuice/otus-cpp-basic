#include "Field.hpp"

namespace field {
    bool checkBounds(int y, int x) {
        return y >= 0 && y < sideSize && x >= 0 && x < sideSize;
    }

    bool setState(Field &field, State state, int y, int x) {
        bool ok = checkBounds(y, x);

        if (ok) {
            field[y][x] = state;
        }
        return ok;
    }

    State getState(const Field &field, int y, int x) {

        if (checkBounds(y, x)) {
            return field[y][x];
        }
        return Invalid;
    }

    bool toStream(std::ostream &out, const Field &field) {
        // TODO: check io errors
        for (int y = 0; y < sideSize; y++) {
            for (int x = 0; x < sideSize; x++) {
                out << static_cast<int>(getState(field, y, x)) << " ";
            }
            out << std::endl;
        }
        return true;
    }


    bool fromStream(std::istream &in, Field &field) {
        int buffer;

        // TODO: check io errors
        for (int y = 0; y < sideSize; y++) {
            for (int x = 0; x < sideSize; x++) {
                in >> buffer;
                setState(field, static_cast<State>(buffer), y, x);
            }
        }
        return true;
    }
}  // namespace field
