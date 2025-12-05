#include "Vehicle.h"
#include "Car.h"

int main() {
    
    std::cout << "\n=== START OF EXERCISE 2 ===\n";

    Vehicle veh;

    veh.brand = "BMW";
    veh.year = 2020;

    veh.setEngineInfo("V8", "Diesel", 200);

    veh.displayVehicleInfo();

    std::cout << std::endl;

    Car c;
    c.brand = "Porsche";
    c.year = 2021;

    c.setEngineInfo("V4", "Gasoline", 120);

    c.displayVehicleInfo();

    std::cout << std::endl;

    Vehicle* vehPtr = new Car;
    vehPtr->brand = "Mercedes";
    vehPtr->year = 2021;

    vehPtr->setEngineInfo("V12", "Hydrogen", 256);

    vehPtr->displayVehicleInfo();

    std::cout << "\n=== END OF EXERCISE 2 ===\n";

    return 0;
}
