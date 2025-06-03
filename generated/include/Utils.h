#ifndef UTILS_H
#define UTILS_H

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
#include "Vehicle.h"
#include "Bus.h"
#include "PriorityVehicle.h"
#include "Orientation.h"

class Street;
class Car;

bool intersects(const std::shared_ptr<Street>& street1, const std::shared_ptr<Street>& street2);

Coordinates<int> computeIntersection(const std::shared_ptr<Street>& street1, const std::shared_ptr<Street>& street2);

int distance(const Coordinates<int>& coord1, const Coordinates<int>& coord2);

Color oppositeColor(Color currentColor);

void setStreetStoplights(const std::shared_ptr<Street>& street, Color initialColor, int syncDistance);

void initializeStoplights(std::vector<std::shared_ptr<Street>>& streets, int syncDistance);

Orientation getRandomDirection(Orientation current);

bool isPriorityVehicleNearby(const Coordinates<int>& pos, const std::vector<std::shared_ptr<Vehicle>>& vehicles);

bool vehicleAhead(const Vehicle& vehicle, const std::vector<std::shared_ptr<Vehicle>>& vehicles, float deltaSeconds);

Orientation opposite(Orientation o);

#endif //UTILS_H
