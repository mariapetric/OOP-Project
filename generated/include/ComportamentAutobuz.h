#ifndef COMPORTAMENTAUTOBUZ_H
#define COMPORTAMENTAUTOBUZ_H

#include "ComportamentRulare.h"

class Autobuz;

class ComportamentAutobuz: public ComportamentRulare {
    int timpStationare = 0;
public:
    void ruleaza(std::shared_ptr<Vehicul> self,
                 const std::vector<std::shared_ptr<Vehicul>>& vehicule,
                 int MAX_LENGTH, int MAX_WIDTH, float deltaSecunde) override;
    virtual ~ComportamentAutobuz();
};

#endif
