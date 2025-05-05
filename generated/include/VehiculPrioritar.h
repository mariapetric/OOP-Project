#ifndef VEHICULPRIORITAR_H
#define VEHICULPRIORITAR_H
#include "Vehicul.h"

class VehiculPrioritar : public Vehicul {

protected:
    explicit VehiculPrioritar(int id_, const Coordonate& pozitieVehicul_, Sens sensVehicul_,
             Sens orientareViitoare_, std::shared_ptr<Strada> strada_);
    void afisare(std::ostream& os) const override;
    VehiculPrioritar (const VehiculPrioritar& other);
    VehiculPrioritar &operator= (const VehiculPrioritar& other);

public:
    virtual ~VehiculPrioritar() = default;
    friend std::ostream& operator<<(std::ostream& os, const VehiculPrioritar& obj);
    virtual std::shared_ptr<Vehicul> clone() const override;
};

#endif //VEHICULPRIORITAR_H
