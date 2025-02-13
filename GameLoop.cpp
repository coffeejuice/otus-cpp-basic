#include "Field.cpp"

namespace game {

    void initalizeEmpty(field::Field& field) {
        for (int y=0; y < field::sideSize, y++) {
            for (int x=0; x < field::sideSize, x++) {
                setState(field, field::State::Empty, y, x);
            }
        }
    }


    bool placeShips(field::Field& field, const int playerId, const int* shipsCountPerShipLength, int shipsTypesCount) {
        for (int cellsCount = 1; cellsCount <= shipsTypesCount; cellsCount++) {

            const int shipsCount = shipsCountPerShipLength[cellsCount];

            for (int shipIndex = 0; shipIndex < shipCount; shipIndex++) {
                
                int cellsY[maxShipLength];
                int cellsX[maxShipLength];

                if (!action::getShipCell(playerId, cellsCount, cellsY, cellsX)) {
                    std::cerr << "Wrong user ship input" << std::endl;
                }

                for (int cell = 0; cell < cellsCount; cell++) {
                    setState(field, field::State::Ship, cellY[cell], cellX[cell]);
                }
            }
        }
        return true;
    }

    int playGame() {
        field::Field fields[2];

        for (int playerId: {0, 1}) {
            initalizeEmpty(fields[playerId]);
        }

        const int shipsCountPerShipLength[] = {0, 4, 3, 2, 1};
        const int maxShipLenght = sizeof(shipsCountPerShipLength) - 1;

        for (int playerId: {0, 1}) {
            placeShips(fields[playerId], playerId, shipsCountPerShipLength, sizeof(shipsCountPerShipLength));
        }

        // ships
        // hit
    }

}
