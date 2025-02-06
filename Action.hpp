#pragma once

namespace action {
    bool getTurn(int playerId, int &y, int &x);
    bool getShipCells(int playerId, int cellsCount, int *x, int *y);
} // namespace action
