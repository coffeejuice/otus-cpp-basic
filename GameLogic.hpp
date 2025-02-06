#pragma once
#include "Field.hpp"

namespace game {
    void hit(field::Field& field, int y, int x);  // TODO: return code
    bool isDamegedShipCell(field::Field& field, int y, int x);
    bool isDeadShipCell(field::Field& field, int y, int x);
    // return count of dead (each cell is hit state) cells
    int deadCellsCount(const field::Field& field);
}  // namespace game
