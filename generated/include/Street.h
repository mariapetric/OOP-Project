#ifndef STREET_H
#define STREET_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "Direction.h"
#include "Coordinates.h"
#include "Orientation.h"
#include "Intersection.h"
#include "TrafficSimulationException.h"

class Vehicle;
class Intersection;
class Stoplight;

class Street {
    static int global_id;
    int id;
    std::string name;
    Coordinates<int> startCoordinate;
    Direction streetDirection;
    std::unordered_map<Coordinates<int>, std::weak_ptr<Intersection>> intersections;
    std::unordered_map<Coordinates<int>, std::shared_ptr<Stoplight>> stoplights;
    std::vector<std::pair<Coordinates<int>, int>> speedLimits;

public:
    explicit Street(const std::string &name_, const Coordinates<int> &coord_, Direction direction_,
                    const std::vector<std::pair<Coordinates<int>, int>> &limits);

    ~Street() = default;

    Street(const Street &other);
    Street &operator=(const Street &other);

    friend std::ostream &operator<<(std::ostream &os, const Street &obj);

    const Coordinates<int> &getStartCoordinate() const;
    const Coordinates<int> getEndCoordinate() const;
    const Direction &getDirection() const;

    void addIntersection(const Coordinates<int> &coord, std::shared_ptr<Intersection> intersection);
    void addStoplight(const Coordinates<int> &coord, std::shared_ptr<Stoplight> stoplight);

    std::vector<std::pair<Coordinates<int>, std::shared_ptr<Intersection>>> getSortedIntersections() const;
    std::shared_ptr<Stoplight> getStoplightAtCoord(const Coordinates<int> &coord) const;

    int getId() const;
    std::vector<std::pair<Coordinates<int>, int>> getSortedSpeedLimits() const;
    int getSpeedLimitAtPosition(const Coordinates<int> &position) const;
    std::shared_ptr<Stoplight> getStoplightNearPosition(const Coordinates<int> &position) const;

    bool hasIntersectionWithinDistance(const Coordinates<int> &position, int maxDistance, Orientation vehicleOrientation) const;
    std::shared_ptr<Street> getNextStreet(const Coordinates<int> &position, Orientation newOrientation,
                                          std::shared_ptr<Street> currentStreet) const;

    bool hasIntersectionAtCoord(const Coordinates<int> &coord) const;
};

#endif //STREET_H
