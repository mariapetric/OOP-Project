#ifndef COMPORTAMENTPRIORITAR_H
#define COMPORTAMENTPRIORITAR_H

#include "ComportamentRulare.h"

class VehiculPrioritar;

class ComportamentPrioritar: public ComportamentRulare {
public:
    void ruleaza(std::shared_ptr<Vehicul> self,
                 const std::vector<std::shared_ptr<Vehicul>>& vehicule,
                 int MAX_LENGTH, int MAX_WIDTH, float deltaSecunde) override;
    virtual ~ComportamentPrioritar();
};

#endif
