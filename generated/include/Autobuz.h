
#ifndef AUTOBUZ_H
#define AUTOBUZ_H
#include "Vehicul.h"

class Autobuz : public Vehicul {
private:
    float distantaParcursa = 0.0f;
    int timpStationare = 0;

protected:
    void afisare(std::ostream& os) const override;
    Autobuz (const Autobuz& other);
    Autobuz &operator= (const Autobuz& other);

public:
    explicit Autobuz(const Coordonate<int>& pozitieVehicul_, Sens sensVehicul_,
             Sens orientareViitoare_, const std::shared_ptr<Strada>& strada_, int viteza_, float distantaParcursa_ = 0);
    virtual ~Autobuz() = default;
    friend std::ostream& operator<<(std::ostream& os, const Autobuz& obj);
    virtual std::shared_ptr<Vehicul> clone() const override;
    bool eOpritInStatie() override;
    virtual void updatePosition(float deltaSecunde, int MAX_LENGTH, int MAX_WIDTH);
    int get_timpStationare();
    void set_timpStationare(int timp_);
};

#endif //AUTOBUZ_H
