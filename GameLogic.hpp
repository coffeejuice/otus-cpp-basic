#pragma once
#include "Field.hpp"

namespace game {
    void hit(field::Field& field, int y, int x);  // TODO: return code
    bool isDamagedShipCell(field::Field& field, int y, int x);
    bool isKilledShipCell(field::Field& field, int y, int x);
}