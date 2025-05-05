#ifndef MASINA_H
#define MASINA_H
#include "Vehicul.h"

class Masina : public Vehicul {

protected:
    explicit Masina(int id_, const Coordonate& pozitieVehicul_, Sens sensVehicul_, Sens orientareViitoare_, std::shared_ptr<Strada> strada_);

    void afisare(std::ostream& os) const override;
    Masina (const Masina& other);
    Masina &operator= (const Masina& other);


public:
    virtual ~Masina() = default;
    friend std::ostream& operator<<(std::ostream& os, const Masina& obj);
    virtual std::shared_ptr<Vehicul> clone() const override;
    virtual void ruleaza(const std::vector<std::shared_ptr<Vehicul>>& vehicule, int MAX_LENGTH, int MAX_WIDTH) override;
};

#endif //MASINA_H
