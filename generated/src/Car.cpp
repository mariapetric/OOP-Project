#include "Car.h"
#include "Utils.h"
#include "CarBehaviour.h"

Car::Car(const Coordinates<int> &position_,
         Orientation orientation_, Orientation nextOrientation_,
         const std::shared_ptr<Street> &street_, int speed_)
    : Vehicle(position_, orientation_, nextOrientation_, street_, speed_) {
    setDrivingStrategy(std::make_shared<CarBehaviour>());
}

Car::Car(const Car &other) : Vehicle(other) {
}

Car &Car::operator=(const Car &other) {
    if (this != &other) {
        Vehicle::operator=(other);
    }
    return *this;
}

void Car::print(std::ostream &os) const {
    os << id << " (" << vehiclePosition.get_x() << ", " << vehiclePosition.get_y() << ") "
       << "Speed: " << speed << ", Orientation: ";

    switch (vehicleOrientation) {
        case Orientation::Up: os << "Up"; break;
        case Orientation::Down: os << "Down"; break;
        case Orientation::Left: os << "Left"; break;
        case Orientation::Right: os << "Right"; break;
    }

    os << ", Street: " << (street ? street->getId() : -1) << '\n';
}

std::shared_ptr<Vehicle> Car::clone() const {
    return std::make_shared<Car>(*this);
}

std::ostream &operator<<(std::ostream &os, const Car &obj) {
    obj.print(os);
    return os;
}
