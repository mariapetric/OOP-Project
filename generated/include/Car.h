#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class CarBehaviour;

class Car : public Vehicle {
protected:
    void print(std::ostream &os) const override;

    Car &operator=(const Car &other);

public:
    explicit Car(const Coordinates<int> &position_, Orientation orientation_, Orientation nextOrientation_,
                 const std::shared_ptr<Street> &street_, int speed_);

    Car(const Car &other);

    virtual ~Car() = default;

    friend std::ostream &operator<<(std::ostream &os, const Car &obj);

    std::shared_ptr<Vehicle> clone() const override;
};

#endif // CAR_H
