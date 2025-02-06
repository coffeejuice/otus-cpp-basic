#include "GameLoop.hpp"

#include <iostream>
#include <numeric>

#include "Action.hpp"
#include "Field.hpp"
#include "GameLogic.hpp"

namespace game {

    void initializeEmpty(field::Field& field) {
        for (int y = 0; y < field::sideSize; y++) {
            for (int x = 0; x < field::sideSize; x++) {
                setState(field, field::State::Empty, y, x);
            }
        }
    }

    bool placeShips(field::Field& field, int playerId, const int* numberOfEachTypeShip, int shipsTypesCount) {
        //TODO: check errors

        for (int cellsCount = 1; cellsCount <= shipsTypesCount; cellsCount++) {
            const int shipsCount = numberOfEachTypeShip[cellsCount];

            for (int shipIndex = 0; shipIndex < shipsCount; shipIndex++) {
                int cellsY[4];  // bad constant
                int cellsX[4];

                if (!action::getShipCells(playerId, cellsCount, cellsY, cellsX)) {
                    std::cerr << "Wrong user ship input" << std::endl;
                }

                for (int cell = 0; cell < cellsCount; cell++) {
                    // if out of bounds
                    setState(field, field::State::Ship, cellsY[cell], cellsX[cell]);
                }
            }
        }
        return true;
    }

    bool areAllShipsDead(const field::Field& field, const int totalShipsCells) {
        return deadCellsCount(field) == totalShipsCells;
    }

    int gameLoop(field::Field* fields, const int totalShipsCells) {
        while (true) {

            for (int playerId: {0, 1}) {
                const int opponentId = 1 - playerId;

                int y;
                int x;
                if (!action::getTurn(playerId, y, x)) {
                    std::cerr << "Game stopped" << std::endl;
                    return -1;
                }
                hit(fields[opponentId], y, x);

                if (areAllShipsDead(fields[opponentId], totalShipsCells)) {
                    return playerId;
                }
            }
        }
        return -1;
    }

    int playGame() {
        field::Field fields[2];

        for (int playerId: {0, 1}) {
            initializeEmpty(fields[playerId]);
        }

        const int numberOfEachTypeShip[] = {0, 4, 3, 2, 1};
        const int totalShipsCells =
            std::accumulate(std::begin(numberOfEachTypeShip), std::end(numberOfEachTypeShip), 0);

        for (int playerId: {0, 1}) {
            placeShips(fields[playerId], playerId, numberOfEachTypeShip, std::size(numberOfEachTypeShip));
        }

        return gameLoop(fields, totalShipsCells);
    }
}  // namespace game