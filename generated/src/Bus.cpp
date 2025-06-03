#include "Bus.h"
#include "BusBehaviour.h"

Bus::Bus(const Coordinates<int> &position_,
         Orientation orientation_, Orientation nextOrientation_,
         const std::shared_ptr<Street> &street_, int speed_, float distanceTraveled_, int stopTime_)
    : Vehicle(position_, orientation_, nextOrientation_, street_, speed_),
      distanceTraveled(distanceTraveled_), stopTime{stopTime_} {
    setDrivingStrategy(std::make_shared<BusBehaviour>());
}

Bus::Bus(const Bus &other)
    : Vehicle(other), distanceTraveled(other.distanceTraveled), stopTime(other.stopTime) {
}

Bus &Bus::operator=(const Bus &other) {
    if (this != &other) {
        Vehicle::operator=(other);
        distanceTraveled = other.distanceTraveled;
        stopTime = other.stopTime;
    }
    return *this;
}

void Bus::print(std::ostream &os) const {
    os << "[Bus] ID: " << id << ", Position: (" << vehiclePosition.get_x()
       << ", " << vehiclePosition.get_y() << "), Speed: " << speed
       << ", Orientation: ";

    switch (vehicleOrientation) {
        case Orientation::Up: os << "Up"; break;
        case Orientation::Down: os << "Down"; break;
        case Orientation::Left: os << "Left"; break;
        case Orientation::Right: os << "Right"; break;
    }

    os << ", Street ID: " << (street ? street->getId() : -1)
       << ", Distance traveled: " << distanceTraveled << "m";

    if (distanceTraveled > 0 && distanceTraveled >= 10.0f) {
        os << " [Station stop]";
    }
    os << '\n';
}

std::shared_ptr<Vehicle> Bus::clone() const {
    return std::make_shared<Bus>(*this);
}

std::ostream &operator<<(std::ostream &os, const Bus &obj) {
    obj.print(os);
    return os;
}

bool Bus::isStoppedAtStation() {
    if (distanceTraveled >= 100.0f) {
        distanceTraveled -= 100.0f; // retain extra distance (e.g. 112 → keep 12)
        return true;
    }
    return false;
}

void Bus::updatePosition(float deltaSeconds, int MAX_LENGTH, int MAX_WIDTH) {
    float dx = 0.f, dy = 0.f;
    switch (vehicleOrientation) {
        case Orientation::Up:
            dy = static_cast<float>(speed) * deltaSeconds * 20.0f;
            break;
        case Orientation::Down:
            dy = -static_cast<float>(speed) * deltaSeconds * 20.0f;
            break;
        case Orientation::Right:
            dx = static_cast<float>(speed) * deltaSeconds * 20.0f;
            break;
        case Orientation::Left:
            dx = -static_cast<float>(speed) * deltaSeconds * 20.0f;
            break;
    }

    float newX = static_cast<float>(vehiclePosition.get_x()) + dx;
    float newY = static_cast<float>(vehiclePosition.get_y()) + dy;

    vehiclePosition.set_x(static_cast<int>(std::round(newX)));
    vehiclePosition.set_y(static_cast<int>(std::round(newY)));

    distanceTraveled += std::fabs(dx) + std::fabs(dy);

    if (vehiclePosition.get_x() < 0)
        vehiclePosition.set_x(0);
    else if (vehiclePosition.get_x() > MAX_LENGTH)
        vehiclePosition.set_x(MAX_LENGTH);

    if (vehiclePosition.get_y() < 0)
        vehiclePosition.set_y(0);
    else if (vehiclePosition.get_y() > MAX_WIDTH)
        vehiclePosition.set_y(MAX_WIDTH);
}

int Bus::getStopTime() const {
    return stopTime;
}

void Bus::setStopTime(int time_) {
    stopTime = time_;
}
