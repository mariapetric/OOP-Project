#ifndef VEHICULPRIORITAR_H
#define VEHICULPRIORITAR_H
#include "Vehicul.h"

class VehiculPrioritar : public Vehicul {

protected:
    void afisare(std::ostream& os) const override;
    VehiculPrioritar (const VehiculPrioritar& other);
    VehiculPrioritar &operator= (const VehiculPrioritar& other);

public:
    explicit VehiculPrioritar(const Coordonate<int>& pozitieVehicul_, Sens sensVehicul_,
             Sens orientareViitoare_, const std::shared_ptr<Strada>& strada_, int viteza_);
    virtual ~VehiculPrioritar() = default;
    friend std::ostream& operator<<(std::ostream& os, const VehiculPrioritar& obj);
    virtual std::shared_ptr<Vehicul> clone() const override;
};

#endif //VEHICULPRIORITAR_H
