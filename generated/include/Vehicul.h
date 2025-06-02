
#ifndef VEHICUL_H
#define VEHICUL_H

#include <iostream>
#include <vector>
#include <memory>
#include "Coordonate.h"
#include "Strada.h"
#include "Sens.h"
#include "TrafficSimulationException.h"
#include "ComportamentRulare.h"

const int MAX_LENGTH = 1000;
const int MAX_WIDTH = 1000;

class Vehicul : public std::enable_shared_from_this<Vehicul> {

protected:
    static int global_id;
    int id;
    Coordonate<int> pozitieVehicul;
    Sens sensVehicul;
    Sens orientareViitoare;
    std::shared_ptr <Strada> strada;
    int viteza;
    std::shared_ptr<ComportamentRulare> strategieRulare;

    explicit Vehicul(const Coordonate<int>& pozitieVehicul_, Sens sensVehicul_, Sens orientareViitoare_, const std::shared_ptr<Strada>& strada_, int viteza_);
    virtual void afisare(std::ostream& os) const = 0;
    Vehicul (const Vehicul& other);
    Vehicul &operator= (const Vehicul& other);

public:
    ~Vehicul() = default;
    friend std::ostream& operator<< (std::ostream& os, const Vehicul& obj);
    virtual std::shared_ptr<Vehicul> clone() const = 0;
    Sens get_Sens() const;
    Sens get_orientareViitoare() const;
    Coordonate<int> get_PozitieVehicul() const;
    std::shared_ptr<Strada> get_Strada() const;
    int get_Id() const;
    void set_orientareViitoare (Sens sensVehicul_);
    void set_Viteza(int viteza_);
    int get_Viteza() const;
    void set_Pozitie(Coordonate<int> poz);

    virtual void updatePosition(float deltaSecunde, int MAX_LENGTH, int MAX_WIDTH); //cand se misca
    void schimbaSensul (Sens nouSens); //in intersectii sau cand "iese" din cadru
	void schimbaStrada (std::shared_ptr<Strada> stradaNoua); //in intersectii
    //virtual void ruleaza(const std::vector<std::shared_ptr<Vehicul>>& vehicule, int MAX_LENGTH, int MAX_WIDTH) = 0;
    virtual bool eOpritInStatie();

    void setStrategieRulare (std::shared_ptr<ComportamentRulare> strategieRulare_);
    virtual void ruleaza (const std::vector<std::shared_ptr<Vehicul>>& vehicule,
        int MAX_LENGTH, int MAX_WIDTH, float deltaSecunde);
};

#endif //VEHICUL_H
