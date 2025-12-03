#include "Vehicle.h"

int main() {
    
    std::cout << "\n=== START OF EXERCISE 2 ===\n";

    Vehicle veh;

    veh.brand = "BMW";
    veh.year = 2020;

    veh.setEngineInfo("V8", "Diesel", 200);

    veh.displayVehicleInfo();

    std::cout << "\n=== END OF EXERCISE 2 ===\n";

    return 0;
}
