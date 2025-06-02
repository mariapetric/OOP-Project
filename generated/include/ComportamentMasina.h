#ifndef COMPORTAMENTMASINA_H
#define COMPORTAMENTMASINA_H

#include "ComportamentRulare.h"

class Masina;

class ComportamentMasina : public ComportamentRulare {
public:
    void ruleaza(std::shared_ptr<Vehicul> self,
                 const std::vector<std::shared_ptr<Vehicul>>& vehicule,
                 int MAX_LENGTH, int MAX_WIDTH, float deltaSecunde) override;
    virtual ~ComportamentMasina();
};

#endif
