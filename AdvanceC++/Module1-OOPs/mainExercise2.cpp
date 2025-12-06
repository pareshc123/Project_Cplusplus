#include "Vehicle.h"
#include "Car.h"

int main() {
    
    std::cout << "\n=== START OF EXERCISE 2 ===\n";

    std::cout << "Invoke Class function using Vehicle Class: " << std::endl;
    Vehicle veh;
    veh.brand = "BMW";
    veh.year = 2020;
    veh.setEngineInfo("V8", "Diesel", 200);
    veh.displayVehicleInfo();
    
    std::cout << std::endl;

    std::cout << "Invoke Class function using CAR Class: " << std::endl;
    Car c;
    c.brand = "Porsche";
    c.year = 2021;
    c.setEngineInfo("V4", "Gasoline", 120);
    c.displayVehicleInfo();

    std::cout << std::endl;

    std::cout << "\nInvoke Class function using CAR Class via pointer: " << std::endl;
    Vehicle* vehPtr = new Car(" ", 0, 0);       // random information about car
    vehPtr->brand = "Mercedes";
    vehPtr->year = 2021;
    vehPtr->setEngineInfo("V12", "Hydrogen", 256);
    vehPtr->displayVehicleInfo();
    delete vehPtr;

    std::cout << std::endl;

    std::cout << "\nInvoke Class function using CAR Class via pointer Array: " << std::endl;
    Car cars[3] = {
    Car("BMW", 2020, 4),
    Car("Audi", 2021, 2),
    Car("Mercedes", 2022, 4)
    };

    Car* ptr = cars;
    for (int i = 0; i < 3; ++i) {
        (ptr + i)->displayVehicleInfo();
    }

    std::cout << "\n=== END OF EXERCISE 2 ===\n";

    return 0;
}
