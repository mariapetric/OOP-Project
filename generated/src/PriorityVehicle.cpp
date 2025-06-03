#include "PriorityVehicle.h"
#include "PriorityBehaviour.h"

PriorityVehicle::PriorityVehicle(const Coordinates<int> &position_,
                                 Orientation orientation_, Orientation nextOrientation_,
                                 const std::shared_ptr<Street> &street_, int speed_)
    : Vehicle(position_, orientation_, nextOrientation_, street_, speed_) {
    setDrivingStrategy(std::make_shared<PriorityBehaviour>());
}

PriorityVehicle::PriorityVehicle(const PriorityVehicle &other)
    : Vehicle(other) {
}

PriorityVehicle &PriorityVehicle::operator=(const PriorityVehicle &other) {
    if (this != &other) {
        Vehicle::operator=(other);
    }
    return *this;
}

void PriorityVehicle::print(std::ostream &os) const {
    os << "[PriorityVehicle]: " << id
       << ", Position: (" << vehiclePosition.get_x() << ", " << vehiclePosition.get_y() << ")"
       << ", Speed: " << speed
       << ", Orientation: ";

    switch (vehicleOrientation) {
        case Orientation::Up: os << "Up"; break;
        case Orientation::Down: os << "Down"; break;
        case Orientation::Left: os << "Left"; break;
        case Orientation::Right: os << "Right"; break;
    }

    os << ", Street ID: " << (street ? street->getId() : -1) << '\n';
}

std::shared_ptr<Vehicle> PriorityVehicle::clone() const {
    return std::make_shared<PriorityVehicle>(*this);
}

std::ostream &operator<<(std::ostream &os, const PriorityVehicle &obj) {
    obj.print(os);
    return os;
}
