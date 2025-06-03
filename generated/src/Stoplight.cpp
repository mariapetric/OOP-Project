#include <iostream>
#include <memory>
#include "Coordinates.h"
#include "Street.h"
#include "Stoplight.h"

Stoplight::Stoplight(double remainingGreenTime_, double remainingYellowTime_, double remainingRedTime_,
                     const Coordinates<int> &coordinates_,
                     std::shared_ptr<Street> street)
        : greenTime{remainingGreenTime_}, yellowTime{remainingYellowTime_},
          redTime{remainingRedTime_}, stoplightCoordinates{coordinates_}, street{street} {
}

std::ostream &operator<<(std::ostream &os, const Stoplight &obj) {
    if (obj.greenTime > 0) {
        os << "Green (" << obj.greenTime << " seconds)";
    } else if (obj.yellowTime > 0) {
        os << "Yellow (" << obj.yellowTime << " seconds)";
    } else if (obj.redTime > 0) {
        os << "Red (" << obj.redTime << " seconds)";
    }
    os << obj.stoplightCoordinates;
    if (auto street_ptr = obj.street.lock())
        os << ' ' << (*street_ptr) << '\n';
    else os << '\n';
    return os;
}

Coordinates<int> Stoplight::getCoordinates() const {
    return stoplightCoordinates;
}

Color Stoplight::getColor() const {
    if (greenTime > 0.0) {
        return Color::Green;
    } else if (yellowTime > 0.0) {
        return Color::Yellow;
    } else if (redTime > 0.0) {
        return Color::Red;
    }
    return Color::Red;
}

void Stoplight::setColor(Color color) {
    switch (color) {
        case Color::Green:
            greenTime = 10.0;
            yellowTime = 0.0;
            redTime = 0.0;
            break;
        case Color::Yellow:
            greenTime = 0.0;
            yellowTime = 2.0;
            redTime = 0.0;
            break;
        case Color::Red:
            greenTime = 0.0;
            yellowTime = 0.0;
            redTime = 12.0;
            break;
        default:
            throw std::invalid_argument("Unknown color in setColor.");
    }
}

void Stoplight::update(double deltaTime) {
    if (greenTime > 0) {
        greenTime -= deltaTime;
        if (greenTime <= 0) {
            setColor(Color::Yellow);
        }
    } else if (yellowTime > 0) {
        yellowTime -= deltaTime;
        if (yellowTime <= 0) {
            setColor(Color::Red);
        }
    } else if (redTime > 0) {
        redTime -= deltaTime;
        if (redTime <= 0) {
            setColor(Color::Green);
        }
    }
}

std::shared_ptr<Street> Stoplight::getStreet() const {
    return street.lock();
}
