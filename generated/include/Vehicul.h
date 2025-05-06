
#ifndef VEHICUL_H
#define VEHICUL_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Coordonate.h"
#include "Strada.h"
#include "Sens.h"
#include "TrafficSimulationException.h"

const int MAX_LENGTH = 1000;
const int MAX_WIDTH = 1000;

class Vehicul {

protected:
    int id;
    int viteza;
    Coordonate pozitieVehicul;
    Sens sensVehicul;
    Sens orientareViitoare;
    std::shared_ptr <Strada> strada;

    explicit Vehicul(int id_, const Coordonate& pozitieVehicul_, Sens sensVehicul_, Sens orientareViitoare_, std::shared_ptr<Strada> strada_);
    virtual void afisare(std::ostream& os) const = 0;
    Vehicul (const Vehicul& other);
    Vehicul &operator= (const Vehicul& other);

public:
    ~Vehicul() = default;
    friend std::ostream& operator<< (std::ostream& os, const Vehicul& obj);
    virtual std::shared_ptr<Vehicul> clone() const = 0;
    Sens get_Sens() const;
    Coordonate get_PozitieVehicul() const;
    std::shared_ptr<Strada> get_Strada() const;
    int get_Id() const;
    void set_orientareViitoare (Sens sensVehicul_);

    void updatePosition(int MAX_LENGTH, int MAX_WIDTH); //cand se misca
    void schimbaSensul (Sens nouSens); //in intersectii sau cand "iese" din cadru
	void schimbaStrada (std::shared_ptr<Strada> stradaNoua); //in intersectii
    virtual void ruleaza(const std::vector<std::shared_ptr<Vehicul>>& vehicule, int MAX_LENGTH, int MAX_WIDTH) = 0;
    virtual bool eOpritInStatie() const;
};

#endif //VEHICUL_H
