#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <iostream>
#include <memory>
#include "Coordinates.h"
#include "Vehicle.h"

class Street;

class Intersection {
    Coordinates<int> intersectionCoordinates;
    std::shared_ptr<Street> verticalStreet;
    std::shared_ptr<Street> horizontalStreet;

public:
    explicit Intersection(const Coordinates<int>& coord_,
                          std::shared_ptr<Street> vertical_,
                          std::shared_ptr<Street> horizontal_);
    ~Intersection() = default;

    friend std::ostream& operator<<(std::ostream& os, const Intersection& obj);

    std::shared_ptr<Street> get_OtherStreet(const std::shared_ptr<Street>& currentStreet) const;
    Coordinates<int> get_Coordinates() const;
    std::shared_ptr<Street> get_VerticalStreet() const;
    std::shared_ptr<Street> get_HorizontalStreet() const;
};

#endif // INTERSECTION_H
