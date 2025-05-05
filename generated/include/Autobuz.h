
#ifndef AUTOBUZ_H
#define AUTOBUZ_H
#include "Vehicul.h"

class Autobuz : public Vehicul {
private:
    int distantaParcursa;

protected:
    explicit Autobuz(int id_, const Coordonate& pozitieVehicul_, Sens sensVehicul_,
             Sens orientareViitoare_, std::shared_ptr<Strada> strada_, int distantaParcursa_ = 0);
    void afisare(std::ostream& os) const override;
    Autobuz (const Autobuz& other);
    Autobuz &operator= (const Autobuz& other);

public:
    virtual ~Autobuz() = default;
    friend std::ostream& operator<<(std::ostream& os, const Autobuz& obj);
    virtual std::shared_ptr<Vehicul> clone() const override;
    bool eOpritInStatie() const override;
};

#endif //AUTOBUZ_H
