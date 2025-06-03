#ifndef STOPLIGHT_H
#define STOPLIGHT_H

#include <iostream>
#include <memory>
#include "Coordinates.h"

class Street;

enum class Color { Green, Yellow, Red };

class Stoplight {
    double greenTime, yellowTime, redTime;
    Coordinates<int> stoplightCoordinates;
    std::weak_ptr<Street> street;

public:
    explicit Stoplight(double remainingGreenTime, double remainingYellowTime, double remainingRedTime,
                       const Coordinates<int> &coordinates, std::shared_ptr<Street> street);

    ~Stoplight() = default;

    friend std::ostream &operator<<(std::ostream &os, const Stoplight &obj);

    Color getColor() const;

    void setColor(Color color);

    Coordinates<int> getCoordinates() const;

    void update(double deltaTime);

    std::shared_ptr<Street> getStreet() const;
};

#endif // STOPLIGHT_H

