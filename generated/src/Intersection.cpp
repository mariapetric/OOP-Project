#include <iostream>
#include <memory>
#include "Coordinates.h"
#include "Intersection.h"
#include "Street.h"

Intersection::Intersection(const Coordinates<int> &coord_,
                           std::shared_ptr<Street> vertical_,
                           std::shared_ptr<Street> horizontal_)
    : intersectionCoordinates{coord_},
      verticalStreet{vertical_},
      horizontalStreet{horizontal_} {
}

std::ostream &operator<<(std::ostream &os, const Intersection &obj) {
    os << obj.intersectionCoordinates << ' ' << *obj.verticalStreet << ' ' << *obj.horizontalStreet << '\n';
    return os;
}

std::shared_ptr<Street> Intersection::get_OtherStreet(const std::shared_ptr<Street> &street) const {
    if (street == verticalStreet) return horizontalStreet;
    if (street == horizontalStreet) return verticalStreet;
    return nullptr;
}

Coordinates<int> Intersection::get_Coordinates() const {
    return intersectionCoordinates;
}

std::shared_ptr<Street> Intersection::get_VerticalStreet() const {
    return verticalStreet;
}

std::shared_ptr<Street> Intersection::get_HorizontalStreet() const {
    return horizontalStreet;
}
