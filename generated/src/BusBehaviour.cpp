#include "BusBehaviour.h"
#include "Bus.h"
#include "Street.h"
#include "Stoplight.h"
#include "Utils.h"
#include "Orientation.h"

BusBehaviour::~BusBehaviour() = default;

void BusBehaviour::drive(
    std::shared_ptr<Vehicle> self,
    const std::vector<std::shared_ptr<Vehicle>> &vehicles,
    int MAX_LENGTH, int MAX_WIDTH,
    float deltaSeconds
) {
    auto bus = std::dynamic_pointer_cast<Bus>(self);
    if (!bus) return;

    auto street = bus->get_Street();
    auto position = bus->get_Position();
    auto orientation = bus->get_Orientation();

    bus->set_Speed(
        street->getSpeedLimitAtPosition(position)
    );

    auto stoplight = street->getStoplightAtCoord(position);
    if (stoplight && stoplight->getColor() == Color::Red)
        return;

    if ((stoplight && stoplight->getColor() == Color::Green &&
         isPriorityVehicleNearby(position, vehicles)) ||
        vehicleAhead(*bus, vehicles, deltaSeconds)) {
        return;
    }

    const int INTERSECTION_DISTANCE = 10;
    if (street->hasIntersectionWithinDistance(position, INTERSECTION_DISTANCE, orientation)) {
        Orientation newDir = getRandomDirection(orientation);
        if (newDir != opposite(orientation)) {
            bus->set_NextOrientation(newDir);
        }
    }

    int delta = bus->get_Speed() / 10;
    if (street->hasIntersectionWithinDistance(position, delta, orientation)) {
        Coordinates<int> foundIntersection;
        for (int i = 0; i <= delta; ++i) {
            Coordinates<int> c = position;
            switch (orientation) {
                case Orientation::Up: c = Coordinates{c.get_x(), c.get_y() - i}; break;
                case Orientation::Down: c = Coordinates{c.get_x(), c.get_y() + i}; break;
                case Orientation::Left: c = Coordinates{c.get_x() - i, c.get_y()}; break;
                case Orientation::Right: c = Coordinates{c.get_x() + i, c.get_y()}; break;
            }
            if (street->hasIntersectionAtCoord(c)) {
                foundIntersection = c;
                bus->set_Position(c);
                break;
            }
        }

        Orientation next = bus->get_NextOrientation();
        if (next != opposite(orientation)) {
            bus->changeOrientation(next);
            auto nextStreet = street->getNextStreet(foundIntersection, next, street);
            if (nextStreet) {
                bus->changeStreet(nextStreet);
            }
        }
    }

    int x = position.get_x();
    int y = position.get_y();
    if ((orientation == Orientation::Left && x <= 0) ||
        (orientation == Orientation::Right && x >= MAX_LENGTH) ||
        (orientation == Orientation::Down && y <= 0) ||
        (orientation == Orientation::Up && y >= MAX_WIDTH)) {
        bus->changeOrientation(opposite(orientation));
    }

    bus->updatePosition(deltaSeconds, MAX_LENGTH, MAX_WIDTH);
}
