#ifndef BUS_BEHAVIOUR_H
#define BUS_BEHAVIOUR_H

#include "Behaviour.h"

class Bus;

class BusBehaviour : public Behaviour {
    int stopTime = 0;

public:
    void drive(std::shared_ptr<Vehicle> self,
               const std::vector<std::shared_ptr<Vehicle>> &vehicles,
               int MAX_LENGTH, int MAX_WIDTH, float deltaSeconds) override;

    virtual ~BusBehaviour();
};

#endif // BUS_BEHAVIOUR_H
