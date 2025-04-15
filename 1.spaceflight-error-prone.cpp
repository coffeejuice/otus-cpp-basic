#include <iostream>

namespace details {
    enum class Oxidizing {
        Oxygen,
        Ozone,
        //...
    };

    struct Engine {
        bool pumpFuel() {
            return true;
        }
        bool turbopump() {
            return true;
        }
        bool fire() {
            return true;
        }
        bool run() {
            return pumpFuel() && turbopump() && /*...*/ fire();
        }
        void setOxidizingAgent(Oxidizing oxidizing) {
            oxidizingAgent = oxidizing;
        }
        Oxidizing oxidizingAgent;
    };
    struct CrewCapsule {
        //...
    };
    struct FuelTank {
        //...
    };
    struct NavigationSystem {
        // ...
    };
    //...
}

class Spaceflight {
public:
    details::Engine engine;
    details::CrewCapsule crewCapsule;
    details::FuelTank fuel;
    details::NavigationSystem navSystem;
};

struct Location {
    double x;
    double y;
};

class Payload {};
class Fuel {};

Spaceflight runSpaceflight() {
    Spaceflight s;
    // кажется, это не то, что требуется для запуска корабля...
    s.engine.fire();
    return s;
}

int main() {
    runSpaceflight();
}