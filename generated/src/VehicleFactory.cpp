#include "VehicleFactory.h"
#include <stdexcept>

std::shared_ptr<Vehicle> VehicleFactory::createVehicle(
    VehicleType type,
    const Coordinates<int>& pos,
    Orientation orientation,
    Orientation futureOrientation,
    std::shared_ptr<Street> street,
    int speed
) {
    switch (type) {
        case VehicleType::Car:
            return std::make_shared<Car>(pos, orientation, futureOrientation, street, speed);
        case VehicleType::Bus:
            return std::make_shared<Bus>(pos, orientation, futureOrientation, street, speed);
        case VehicleType::Priority:
            return std::make_shared<PriorityVehicle>(pos, orientation, futureOrientation, street, speed);
        default:
            throw std::invalid_argument("Unknown VehicleType.");
    }
}
