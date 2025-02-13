#pragma once

#include <ostream>

namespace field {
    static constexpr int sideSize = 10;
    enum State {
        Empty,
        Ship,
        DamagedShip,
        KilledShip,
    };

    using Field = State[sideSize][sideSize];

    bool setState(Field& filed, State& state, int y, int x);
    bool getState(const Field& field, int y, int x);

    bool toStream(std::ostream& out, Field& field);
    bool fromStream(std::istream& in, Field& field);
}