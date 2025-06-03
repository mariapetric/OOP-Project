#include "Vehicle.h"

int Vehicle::global_id = 1;

Vehicle::Vehicle(const Coordinates<int> &position_, Orientation orientation_, Orientation nextOrientation_,
                 const std::shared_ptr<Street> &street_, int speed_) : id{global_id++},
                                                                       vehiclePosition{position_},
                                                                       vehicleOrientation{orientation_},
                                                                       nextOrientation{nextOrientation_},
                                                                       street{street_}, speed{speed_} {
    if (!street) {
        throw InvalidStartPositionException("Vehicle cannot be placed on a null street.");
    }

    if (position_.get_x() < 0 || position_.get_x() > MAX_LENGTH || position_.get_y() < 0 ||
        position_.get_y() > MAX_WIDTH) {
        throw InvalidStartPositionException("Vehicle position is outside screen limits.");
    }
}

Vehicle::Vehicle(const Vehicle &other) : std::enable_shared_from_this<Vehicle>(other),
                                         id{other.id}, vehiclePosition{other.vehiclePosition},
                                         vehicleOrientation{other.vehicleOrientation}, nextOrientation{other.nextOrientation},
                                         street{other.street}, speed{other.speed} {
}

Vehicle &Vehicle::operator=(const Vehicle &other) {
    if (this != &other) {
        id = other.id;
        vehiclePosition = other.vehiclePosition;
        vehicleOrientation = other.vehicleOrientation;
        nextOrientation = other.nextOrientation;
        street = other.street;
        speed = other.speed;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Vehicle &obj) {
    obj.print(os);
    return os;
}

Orientation Vehicle::get_Orientation() const {
    return vehicleOrientation;
}

Coordinates<int> Vehicle::get_Position() const {
    return vehiclePosition;
}

std::shared_ptr<Street> Vehicle::get_Street() const {
    return street;
}

int Vehicle::get_Id() const {
    return id;
}

void Vehicle::set_NextOrientation(Orientation orientation) {
    nextOrientation = orientation;
}

Orientation Vehicle::get_NextOrientation() const {
    return nextOrientation;
}

void Vehicle::set_Speed(int speed_) {
    speed = speed_;
}

int Vehicle::get_Speed() const {
    return speed;
}

void Vehicle::set_Position(Coordinates<int> position) {
    vehiclePosition = position;
}

void Vehicle::updatePosition(float deltaSeconds, int MAX_LENGTH, int MAX_WIDTH) {
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

    if (vehiclePosition.get_x() < 0)
        vehiclePosition.set_x(0);
    else if (vehiclePosition.get_x() > MAX_LENGTH)
        vehiclePosition.set_x(MAX_LENGTH);

    if (vehiclePosition.get_y() < 0)
        vehiclePosition.set_y(0);
    else if (vehiclePosition.get_y() > MAX_WIDTH)
        vehiclePosition.set_y(MAX_WIDTH);
}

void Vehicle::changeOrientation(Orientation newOrientation) {
    vehicleOrientation = newOrientation;
    nextOrientation = newOrientation;
}

void Vehicle::changeStreet(std::shared_ptr<Street> newStreet) {
    street = newStreet;
}

bool Vehicle::isStoppedAtStation() {
    return false;
}

void Vehicle::setDrivingStrategy(std::shared_ptr<Behaviour> drivingStrategy_) {
    drivingStrategy = drivingStrategy_;
}

void Vehicle::drive(const std::vector<std::shared_ptr<Vehicle> > &vehicles,
                    int MAX_LENGTH, int MAX_WIDTH, float deltaSeconds) {
    if (drivingStrategy)
        drivingStrategy->drive(shared_from_this(), vehicles, MAX_LENGTH, MAX_WIDTH, deltaSeconds);
}
