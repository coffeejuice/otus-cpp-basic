#pragma once
#include <istream>
#include <ostream>

namespace field {
    static constexpr int sideSize = 10;

    enum State { Empty, Ship, DamagedShip, DeadShip, Invalid };

    using Field = State[sideSize][sideSize];

    bool setState(Field &field, State state, int y, int x);
    State getState(const Field &field, int y, int x);
    bool toStream(std::ostream &out, const Field &field);
    bool fromStream(std::istream &in, Field &field);
}  // namespace field
