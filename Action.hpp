#pragma once

namespace action {
    bool getTurn(const int playerId, int& y, int& x);
    bool getShipCell(const int playerId, int cellsCount, int* x, int* y)
}