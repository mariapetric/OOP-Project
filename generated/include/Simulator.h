#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_set>
#include <queue>
#include <random>

#include "Coordinates.h"
#include "Intersection.h"
#include "Stoplight.h"
#include "Utils.h"
#include "Vehicle.h"
#include "Bus.h"
#include "PriorityVehicle.h"
#include "Orientation.h"
#include "Street.h"
#include "Car.h"

// Singleton for the simulator
class Simulator {
private:
    std::vector<std::shared_ptr<Street>> streets;
    std::vector<std::shared_ptr<Intersection>> intersections;
    std::vector<std::shared_ptr<Stoplight>> stoplights;
    std::vector<std::shared_ptr<Vehicle>> vehicles;
    double currentTime = 0.0;

    Simulator() = default;                      // private constructor
    Simulator(const Simulator &) = delete;      // disable copy constructor
    Simulator &operator=(const Simulator &) = delete; // disable assignment

public:
    static Simulator &getInstance() {
        static Simulator instance; // single instance initialization
        return instance;
    }

    void addStreet(const std::shared_ptr<Street> s);

    void addIntersection(const std::shared_ptr<Intersection> i);

    void addStoplight(const std::shared_ptr<Stoplight> s);

    void addVehicle(const std::shared_ptr<Vehicle> v);

    void simulateTime(double deltaSeconds);

    int getCurrentTime() const;

    const std::vector<std::shared_ptr<Vehicle>>& getVehicles() const;

    const std::vector<std::shared_ptr<Street>>& getStreets() const;

    const std::vector<std::shared_ptr<Stoplight>>& getStoplights() const;

    const std::vector<std::shared_ptr<Intersection>>& getIntersections() const;
};

#endif // SIMULATOR_H
