
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_set>
#include <queue>
#include <random>
#include "Coordinates.h"
#include "Street.h"
#include "Intersection.h"
#include "Stoplight.h"
#include "Utils.h"
#include "Vehicle.h"
#include "Bus.h"
#include "PriorityVehicle.h"
#include "Orientation.h"

bool intersects(const std::shared_ptr<Street>& s1, const std::shared_ptr<Street>& s2) {
    return s1->getDirection() != s2->getDirection();
}

Coordinates<int> computeIntersection(const std::shared_ptr<Street>& s1, const std::shared_ptr<Street>& s2) {
    int x = -1, y = -1;
    if (s1->getDirection() == Direction::Vertical && s2->getDirection() == Direction::Horizontal) {
        x = s1->getStartCoordinate().get_x();
        y = s2->getStartCoordinate().get_y();
    } else {
        x = s2->getStartCoordinate().get_x();
        y = s1->getStartCoordinate().get_y();
    }
    return Coordinates{x, y};
}

Color culoare_opusa(Color current) {
    switch (current) {
        case Color::Green: return Color::Red;
        case Color::Yellow: return Color::Red;
        case Color::Red: return Color::Green;
        default: return Color::Red;
    }
}

int distance(const Coordinates<int>& c1, const Coordinates<int>& c2) {
    return std::abs(c1.get_x() - c2.get_x()) + std::abs(c1.get_y() - c2.get_y());
}

void seteazaSemafoarePeStrada(const std::shared_ptr<Street> street, const Color initialColor, int syncDistance) {
    auto intersections = street->getSortedIntersections();
    Color currentColor = initialColor;
    Coordinates<int> lastPos;

    for (size_t i = 0; i < intersections.size(); ++i) {
        auto& [coord, intersection] = intersections[i];
        if (i == 0 || distance(coord, lastPos) > syncDistance) {
            currentColor = culoare_opusa(currentColor);
            lastPos = coord;
        }
        auto light = street->getStoplightAtCoord(coord);
        light->setColor(currentColor);
    }
}

void initializeStoplights(std::vector<std::shared_ptr<Street>>& streets, int syncDistance) {
    std::queue<std::shared_ptr<Street>> q;
    std::unordered_set<int> visited;
    std::unordered_map<int, Color> assignedColors;

    auto startStreet = streets[0];
    q.push(startStreet);
    visited.insert(startStreet->getId());
    assignedColors[startStreet->getId()] = Color::Red;
    seteazaSemafoarePeStrada(startStreet, Color::Red, syncDistance);

    while (!q.empty()) {
        auto currentStreet = q.front();
        q.pop();

        for (auto& [coord, intersection] : currentStreet->getSortedIntersections()) {
            auto neighborStreet = intersection->get_OtherStreet(currentStreet);
            if (visited.find(neighborStreet->getId()) == visited.end()) {
                auto currentLight = currentStreet->getStoplightAtCoord(coord);
                Color opposite = culoare_opusa(currentLight->getColor());

                assignedColors[neighborStreet->getId()] = opposite;
                seteazaSemafoarePeStrada(neighborStreet, opposite, syncDistance);
                q.push(neighborStreet);
                visited.insert(neighborStreet->getId());
            }
        }
    }
}

Orientation getRandomDirection(Orientation current) {
    static std::default_random_engine eng{std::random_device{}()};
    static std::uniform_int_distribution<int> dist(0, 2);
    int opt = dist(eng);

    switch (current) {
        case Orientation::Up: return (opt == 0) ? Orientation::Up : (opt == 1) ? Orientation::Left : Orientation::Right;
        case Orientation::Down: return (opt == 0) ? Orientation::Down : (opt == 1) ? Orientation::Right : Orientation::Left;
        case Orientation::Left: return (opt == 0) ? Orientation::Left : (opt == 1) ? Orientation::Down : Orientation::Up;
        case Orientation::Right: return (opt == 0) ? Orientation::Right : (opt == 1) ? Orientation::Up : Orientation::Down;
    }
    return current;
}

bool isPriorityVehicleNearby(const Coordinates<int>& pos, const std::vector<std::shared_ptr<Vehicle>>& vehicles) {
    for (const auto& v : vehicles) {
        if (auto pv = std::dynamic_pointer_cast<PriorityVehicle>(v)) {
            if (distance(pos, pv->get_Position()) < 10)
                return true;
        }
    }
    return false;
}

bool vehicleAhead(const Vehicle& vehicle, const std::vector<std::shared_ptr<Vehicle>>& vehicles, float deltaSec) {
    const auto& pos = vehicle.get_Position();
    auto orientation = vehicle.get_Orientation();
    auto streetId = vehicle.get_Street()->getId();

    float dxPerFrame = static_cast<float>(vehicle.get_Speed()) * deltaSec * 25.0f;
    int detectionRange = static_cast<int>(std::round(dxPerFrame));
    detectionRange = std::max(detectionRange, 1);

    for (const auto& v : vehicles) {
        if (v->get_Id() == vehicle.get_Id()) continue;
        if (v->get_Street()->getId() != streetId) continue;
        if (v->get_Orientation() != orientation) continue;

        const auto& vPos = v->get_Position();
        int dist = -1;

        switch (orientation) {
            case Orientation::Up:
                if (vPos.get_x() == pos.get_x() && vPos.get_y() <= pos.get_y())
                    dist = pos.get_y() - vPos.get_y();
                break;
            case Orientation::Down:
                if (vPos.get_x() == pos.get_x() && vPos.get_y() >= pos.get_y())
                    dist = vPos.get_y() - pos.get_y();
                break;
            case Orientation::Left:
                if (vPos.get_y() == pos.get_y() && vPos.get_x() <= pos.get_x())
                    dist = pos.get_x() - vPos.get_x();
                break;
            case Orientation::Right:
                if (vPos.get_y() == pos.get_y() && vPos.get_x() >= pos.get_x())
                    dist = vPos.get_x() - pos.get_x();
                break;
        }

        if (dist < 0) continue;

        bool sameLocationAndLowerId = (dist == 0 && v->get_Id() < vehicle.get_Id());

        if ((dist > 0 && dist <= detectionRange) || sameLocationAndLowerId) {
            if (auto bus = std::dynamic_pointer_cast<Bus>(v)) {
                if (bus->isStoppedAtStation()) continue;
            }
            return true;
        }
    }

    return false;
}

Orientation opposite(Orientation o) {
    switch (o) {
        case Orientation::Up: return Orientation::Down;
        case Orientation::Down: return Orientation::Up;
        case Orientation::Left: return Orientation::Right;
        case Orientation::Right: return Orientation::Left;
        default: return o;
    }
}
