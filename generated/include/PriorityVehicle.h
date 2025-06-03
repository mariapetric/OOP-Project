#ifndef PRIORITYVEHICLE_H
#define PRIORITYVEHICLE_H

#include "Vehicle.h"

class PriorityVehicle : public Vehicle {
protected:
    void print(std::ostream &os) const override;


public:
    explicit PriorityVehicle(const Coordinates<int> &position_, Orientation orientation_,
                             Orientation nextOrientation_, const std::shared_ptr<Street> &street_, int speed_);

    virtual ~PriorityVehicle() = default;

    PriorityVehicle(const PriorityVehicle &other);

    PriorityVehicle &operator=(const PriorityVehicle &other);

    friend std::ostream &operator<<(std::ostream &os, const PriorityVehicle &obj);

    virtual std::shared_ptr<Vehicle> clone() const override;
};

#endif // PRIORITYVEHICLE_H
