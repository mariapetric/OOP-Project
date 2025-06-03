#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <memory>
#include <vector>

class Vehicle;

class Behaviour {
public:
    virtual void drive(std::shared_ptr<Vehicle> self,
                       const std::vector<std::shared_ptr<Vehicle>> &vehicles,
                       int MAX_LENGTH, int MAX_WIDTH, float deltaSeconds) = 0;

    virtual ~Behaviour() = default;
};

#endif // BEHAVIOUR_H
