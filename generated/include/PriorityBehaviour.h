#ifndef PRIORITY_BEHAVIOUR_H
#define PRIORITY_BEHAVIOUR_H

#include "Behaviour.h"

class PriorityVehicle;

class PriorityBehaviour : public Behaviour {
public:
    void drive(std::shared_ptr<Vehicle> self,
               const std::vector<std::shared_ptr<Vehicle>> &vehicles,
               int MAX_LENGTH, int MAX_WIDTH, float deltaSeconds) override;

    virtual ~PriorityBehaviour();
};

#endif // PRIORITY_BEHAVIOUR_H
