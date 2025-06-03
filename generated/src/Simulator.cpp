#include "Simulator.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void Simulator::addStreet(const std::shared_ptr<Street> s) {
    streets.push_back(s);
}

void Simulator::addIntersection(const std::shared_ptr<Intersection> i) {
    intersections.push_back(i);
}

void Simulator::addStoplight(const std::shared_ptr<Stoplight> s) {
    stoplights.push_back(s);
}

void Simulator::addVehicle(const std::shared_ptr<Vehicle> v) {
    vehicles.push_back(v);
}

void Simulator::simulateTime(double deltaSeconds) {
    for (auto &stoplight : stoplights) {
        if (stoplight) stoplight->update(deltaSeconds);
    }

    for (auto &v : vehicles) {
        if (v)
            v->drive(vehicles, 1000, 1000, deltaSeconds);
    }

    currentTime += deltaSeconds;
}

int Simulator::getCurrentTime() const {
    return currentTime;
}

const std::vector<std::shared_ptr<Vehicle>> &Simulator::getVehicles() const {
    return vehicles;
}

const std::vector<std::shared_ptr<Street>> &Simulator::getStreets() const {
    return streets;
}

const std::vector<std::shared_ptr<Stoplight>> &Simulator::getStoplights() const {
    return stoplights;
}

const std::vector<std::shared_ptr<Intersection>> &Simulator::getIntersections() const {
    return intersections;
}
