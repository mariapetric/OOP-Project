#ifndef CAR_BEHAVIOUR_H
#define CAR_BEHAVIOUR_H

#include "Behaviour.h"

class Car;

class CarBehaviour : public Behaviour {
public:
    void drive(std::shared_ptr<Vehicle> self,
               const std::vector<std::shared_ptr<Vehicle>> &vehicles,
               int MAX_LENGTH, int MAX_WIDTH, float deltaSeconds) override;

    virtual ~CarBehaviour();
};

#endif // CAR_BEHAVIOUR_H
