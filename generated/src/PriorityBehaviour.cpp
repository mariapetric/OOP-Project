#include "PriorityBehaviour.h"
#include "PriorityVehicle.h"
#include "Street.h"
#include "Stoplight.h"
#include "Utils.h"
#include "Orientation.h"

PriorityBehaviour::~PriorityBehaviour() = default;

void PriorityBehaviour::drive(
    std::shared_ptr<Vehicle> self,
    const std::vector<std::shared_ptr<Vehicle>> &vehicles,
    int MAX_LENGTH, int MAX_WIDTH,
    float deltaSeconds
) {
    auto priority = std::dynamic_pointer_cast<PriorityVehicle>(self);
    if (!priority) return;

    auto street = priority->get_Street();
    auto position = priority->get_Position();
    auto orientation = priority->get_Orientation();

    priority->set_Speed(65);

    const int INTERSECTION_DISTANCE = 10;
    if (street->hasIntersectionWithinDistance(position, INTERSECTION_DISTANCE, orientation)) {
        Orientation newDir = getRandomDirection(orientation);
        if (newDir != opposite(orientation)) {
            priority->set_NextOrientation(newDir);
        }
    }

    int delta = priority->get_Speed() / 10;
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
                priority->set_Position(c);

                for (const auto &v : vehicles) {
                    if (v == self) continue;
                    auto vp = std::dynamic_pointer_cast<PriorityVehicle>(v);
                    if (vp && vp->get_Position() == foundIntersection) {
                        if (orientation == Orientation::Left || orientation == Orientation::Right)
                            return;
                    }
                }

                break;
            }
        }

        Orientation next = priority->get_NextOrientation();
        if (next != opposite(orientation)) {
            priority->changeOrientation(next);
            auto nextStreet = street->getNextStreet(foundIntersection, next, street);
            if (nextStreet) {
                priority->changeStreet(nextStreet);
            }
        }
    }

    int x = position.get_x();
    int y = position.get_y();
    if ((orientation == Orientation::Left && x <= 0) ||
        (orientation == Orientation::Right && x >= MAX_LENGTH) ||
        (orientation == Orientation::Down && y <= 0) ||
        (orientation == Orientation::Up && y >= MAX_WIDTH)) {
        priority->changeOrientation(opposite(orientation));
    }

    priority->updatePosition(deltaSeconds, MAX_LENGTH, MAX_WIDTH);
}
