#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <vector>
#include <memory>
#include "Coordinates.h"
#include "Street.h"
#include "Orientation.h"
#include "TrafficSimulationException.h"
#include "Behaviour.h"

const int MAX_LENGTH = 1000;
const int MAX_WIDTH = 1000;

class Street;

class Vehicle : public std::enable_shared_from_this<Vehicle> {
protected:
    static int global_id;
    int id;
    Coordinates<int> vehiclePosition;
    Orientation vehicleOrientation;
    Orientation nextOrientation;
    std::shared_ptr<Street> street;
    int speed;
    std::shared_ptr<Behaviour> drivingStrategy;

    explicit Vehicle(const Coordinates<int> &position_, Orientation orientation_, Orientation nextOrientation_,
                     const std::shared_ptr<Street> &street_, int speed_);

    virtual void print(std::ostream &os) const = 0;

    Vehicle(const Vehicle &other);

    Vehicle &operator=(const Vehicle &other);

public:
    virtual ~Vehicle() = default;

    friend std::ostream &operator<<(std::ostream &os, const Vehicle &obj);

    virtual std::shared_ptr<Vehicle> clone() const = 0;

    Orientation get_Orientation() const;

    Orientation get_NextOrientation() const;

    Coordinates<int> get_Position() const;

    std::shared_ptr<Street> get_Street() const;

    int get_Id() const;

    void set_NextOrientation(Orientation orientation);

    void set_Speed(int speed_);

    int get_Speed() const;

    void set_Position(Coordinates<int> position);

    virtual void updatePosition(float deltaSeconds, int MAX_LENGTH, int MAX_WIDTH);

    void changeOrientation(Orientation newOrientation);

    void changeStreet(std::shared_ptr<Street> newStreet);

    virtual bool isStoppedAtStation();

    void setDrivingStrategy(std::shared_ptr<Behaviour> drivingStrategy_);

    virtual void drive(const std::vector<std::shared_ptr<Vehicle> > &vehicles,
                       int MAX_LENGTH, int MAX_WIDTH, float deltaSeconds);
};

#endif // VEHICLE_H
