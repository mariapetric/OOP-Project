#ifndef MASINA_H
#define MASINA_H
#include "Vehicul.h"

class ComportamentMasina;

class Masina : public Vehicul {

protected:


    void afisare(std::ostream& os) const override;
    Masina &operator= (const Masina& other);


public:
    explicit Masina(const Coordonate<int>& pozitieVehicul_, Sens sensVehicul_, Sens orientareViitoare_, const std::shared_ptr<Strada>& strada_, int viteza_);
    Masina (const Masina& other);
    virtual ~Masina() = default;
    friend std::ostream& operator<<(std::ostream& os, const Masina& obj);
    virtual std::shared_ptr<Vehicul> clone() const override;
    //virtual void ruleaza(const std::vector<std::shared_ptr<Vehicul>>& vehicule, int MAX_LENGTH, int MAX_WIDTH) override;
};

#endif //MASINA_H
