
#ifndef COMPORTAMENTRULARE_H
#define COMPORTAMENTRULARE_H
#include <memory>
#include <vector>

class Vehicul;

class ComportamentRulare {
public:
    virtual void ruleaza(std::shared_ptr<Vehicul> self,
                         const std::vector<std::shared_ptr<Vehicul>>& vehicule,
                         int MAX_LENGTH, int MAX_WIDTH, float deltaSecunde) = 0;
    virtual ~ComportamentRulare() = default;
};

#endif
