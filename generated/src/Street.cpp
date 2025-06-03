#include "Street.h"
#include "Utils.h"
#include "Coordinates.h"

int Street::global_id = 1;

Street::Street(const std::string &name_,
               const Coordinates<int> &coord_, Direction direction_,
               const std::vector<std::pair<Coordinates<int>, int>> &limits)
               : id{global_id++}, name{name_},
                 startCoordinate{coord_},
                 streetDirection{direction_}, intersections{}, stoplights{}, speedLimits{limits} {
    if (coord_.get_x() < 0 || coord_.get_x() > MAX_LENGTH || coord_.get_y() < 0 || coord_.get_y() > MAX_WIDTH) {
        throw InvalidStartPositionException("Street coordinates are invalid, outside screen limits.");
    }

    for (const auto &limit : limits) {
        if (limit.second < 0) {
            throw VehicleMovementException("Speed limit cannot be negative.");
        }
    }
}

Street::Street(const Street &other) : id{other.id}, name{other.name},
                                      startCoordinate{other.startCoordinate}, streetDirection{other.streetDirection},
                                      intersections{other.intersections}, stoplights{other.stoplights},
                                      speedLimits{other.speedLimits} {}

Street &Street::operator=(const Street &other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        startCoordinate = other.startCoordinate;
        streetDirection = other.streetDirection;
        intersections = other.intersections;
        stoplights = other.stoplights;
        speedLimits = other.speedLimits;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Street &obj) {
    os << obj.id << ' ' << obj.name << ' ' << obj.startCoordinate
       << ' ' << ((obj.streetDirection == Direction::Vertical) ? "Vertical" : "Horizontal") << " Limits: ";
    for (const auto &l : obj.speedLimits)
        os << "[ " << l.first << ", " << l.second << " ]";
    os << '\n';
    return os;
}

const Coordinates<int> &Street::getStartCoordinate() const {
    return startCoordinate;
}

const Coordinates<int> Street::getEndCoordinate() const {
    int x = startCoordinate.get_x();
    int y = startCoordinate.get_y();

    switch (streetDirection) {
        case Direction::Horizontal:
            return Coordinates<int>((x == 0) ? MAX_LENGTH : 0, y);
        case Direction::Vertical:
            return Coordinates<int>(x, (y == 0) ? MAX_WIDTH : 0);
    }
    return startCoordinate;
}

const Direction &Street::getDirection() const {
    return streetDirection;
}

void Street::addIntersection(const Coordinates<int> &coord, std::shared_ptr<Intersection> intersection) {
    intersections[coord] = intersection;
}

void Street::addStoplight(const Coordinates<int> &coord, std::shared_ptr<Stoplight> stoplight) {
    stoplights[coord] = stoplight;
}

std::vector<std::pair<Coordinates<int>, std::shared_ptr<Intersection>>> Street::getSortedIntersections() const {
    std::vector<std::pair<Coordinates<int>, std::shared_ptr<Intersection>>> sorted;
    for (const auto &[coord, inter] : intersections) {
        if (auto sp = inter.lock()) {
            sorted.push_back({coord, sp});
        }
    }
    if (streetDirection == Direction::Horizontal) {
        std::sort(sorted.begin(), sorted.end(), [](const auto &a, const auto &b) {
            return a.first.get_x() < b.first.get_x();
        });
    } else {
        std::sort(sorted.begin(), sorted.end(), [](const auto &a, const auto &b) {
            return a.first.get_y() < b.first.get_y();
        });
    }
    return sorted;
}

std::vector<std::pair<Coordinates<int>, int>> Street::getSortedSpeedLimits() const {
    auto sorted = speedLimits;
    if (streetDirection == Direction::Horizontal) {
        std::sort(sorted.begin(), sorted.end(), [](const auto &a, const auto &b) {
            return a.first.get_x() < b.first.get_x();
        });
    } else {
        std::sort(sorted.begin(), sorted.end(), [](const auto &a, const auto &b) {
            return a.first.get_y() < b.first.get_y();
        });
    }
    return sorted;
}

std::shared_ptr<Stoplight> Street::getStoplightAtCoord(const Coordinates<int> &coord) const {
    auto it = stoplights.find(coord);
    return (it != stoplights.end()) ? it->second : nullptr;
}

int Street::getId() const {
    return id;
}

int Street::getSpeedLimitAtPosition(const Coordinates<int> &pos) const {
    for (const auto &[coord, speed] : speedLimits) {
        if (distance(pos, coord) < 100)
            return speed;
    }
    return 50;
}

std::shared_ptr<Stoplight> Street::getStoplightNearPosition(const Coordinates<int> &pos) const {
    for (const auto &[coord, light] : stoplights) {
        if (distance(pos, coord) < 100) {
            return light;
        }
    }
    return nullptr;
}

bool Street::hasIntersectionWithinDistance(const Coordinates<int> &pos, int maxDist, Orientation vehicleOrientation) const {
    auto sorted = getSortedIntersections();
    for (const auto &[coord, inter] : sorted) {
        if (streetDirection == Direction::Horizontal) {
            if ((vehicleOrientation == Orientation::Right && coord.get_x() > pos.get_x() && coord.get_x() - pos.get_x() <= maxDist) ||
                (vehicleOrientation == Orientation::Left && coord.get_x() < pos.get_x() && pos.get_x() - coord.get_x() <= maxDist))
                return true;
        } else {
            if ((vehicleOrientation == Orientation::Up && coord.get_y() > pos.get_y() && coord.get_y() - pos.get_y() <= maxDist) ||
                (vehicleOrientation == Orientation::Down && coord.get_y() < pos.get_y() && pos.get_y() - coord.get_y() <= maxDist))
                return true;
        }
    }
    return false;
}

std::shared_ptr<Street> Street::getNextStreet(const Coordinates<int> &pos, Orientation newOrientation,
                                              std::shared_ptr<Street> currentStreet) const {
    std::shared_ptr<Street> nextStreet = nullptr;
    int minDistance = std::numeric_limits<int>::max();
    for (const auto &[coord, interWeak] : intersections) {
        if (auto inter = interWeak.lock()) {
            if (inter->get_VerticalStreet() != currentStreet && inter->get_HorizontalStreet() != currentStreet)
                continue;
            int dist = 0;
            if (streetDirection == Direction::Horizontal) {
                if (newOrientation == Orientation::Right && coord.get_x() > pos.get_x()) {
                    dist = coord.get_x() - pos.get_x();
                } else if (newOrientation == Orientation::Left && coord.get_x() < pos.get_x()) {
                    dist = pos.get_x() - coord.get_x();
                }
            } else {
                if (newOrientation == Orientation::Up && coord.get_y() > pos.get_y()) {
                    dist = coord.get_y() - pos.get_y();
                } else if (newOrientation == Orientation::Down && coord.get_y() < pos.get_y()) {
                    dist = pos.get_y() - coord.get_y();
                }
            }
            if (dist < minDistance) {
                minDistance = dist;
                nextStreet = inter->get_OtherStreet(currentStreet);
            }
        }
    }
    return nextStreet;
}

bool Street::hasIntersectionAtCoord(const Coordinates<int> &coord) const {
    return intersections.find(coord) != intersections.end();
}
