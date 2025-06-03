#ifndef VEHICLE_FACTORY_H
#define VEHICLE_FACTORY_H

#include <memory>
#include "Vehicle.h"
#include "Car.h"
#include "Bus.h"
#include "PriorityVehicle.h"

enum class VehicleType {
    Car,
    Bus,
    Priority
};

class VehicleFactory {
public:
    static std::shared_ptr<Vehicle> createVehicle(
        VehicleType type,
        const Coordinates<int>& pos,
        Orientation orientation,
        Orientation futureOrientation,
        std::shared_ptr<Street> street,
        int speed = 70
    );
};

#endif // VEHICLE_FACTORY_H
