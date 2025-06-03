#ifndef BUS_H
#define BUS_H

#include "Vehicle.h"

class Bus : public Vehicle {
private:
    float distanceTraveled = 0.0f;
    int stopTime = 0;

protected:
    void print(std::ostream &os) const override;

public:
    explicit Bus(const Coordinates<int> &position_, Orientation orientation_,
                 Orientation nextOrientation_, const std::shared_ptr<Street> &street_, int speed_,
                 float distanceTraveled_ = 0, int stopTime = 0);

    virtual ~Bus() = default;

    Bus(const Bus &other);

    Bus &operator=(const Bus &other);

    friend std::ostream &operator<<(std::ostream &os, const Bus &obj);

    virtual std::shared_ptr<Vehicle> clone() const override;

    bool isStoppedAtStation() override;

    virtual void updatePosition(float deltaSeconds, int MAX_LENGTH, int MAX_WIDTH) override;

    int getStopTime() const;

    void setStopTime(int time_);
};

#endif //BUS_H
