#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_set>
#include <queue>
#include <random>
#include "Coordonate.h"
#include "Intersectie.h"
#include "Semafor.h"
#include "Utils.h"
#include "Vehicul.h"
#include "Autobuz.h"
#include "VehiculPrioritar.h"
#include "Sens.h"
#include "Strada.h"
#include "Masina.h"
// singleton in simulator

class Simulator {
private:
    std::vector <std::shared_ptr<Strada>> strazi;
    std::vector <std::shared_ptr<Intersectie>> intersectii;
    std::vector <std::shared_ptr<Semafor>> semafoare;
    std::vector <std::shared_ptr<Vehicul>> vehicule;
    double currentTime = 0.0;

    Simulator() = default; // constructor privat
    Simulator(const Simulator&) = delete; // copiere si atribuire sterse
    Simulator& operator=(const Simulator&) = delete;

public:
    static Simulator& getInstance() { // initializare unica
        static Simulator instanta;
        return instanta;
    }

    void adaugaStrada (const std::shared_ptr<Strada> s);
    void adaugaIntersectie(const std::shared_ptr<Intersectie> i);
    void adaugaSemafoare (const std::shared_ptr<Semafor> s);
    void adaugaVehicul(const std::shared_ptr<Vehicul> v);
    void simuleazaTimp(double deltaSecunde);
    int getTimpCurent() const;
    const std::vector<std::shared_ptr<Vehicul>>& getVehicule() const;
    const std::vector <std::shared_ptr<Strada>>& getStrazi() const;
    const std::vector<std::shared_ptr<Semafor>>& getSemafoare() const;
    const std::vector <std::shared_ptr<Intersectie>>& getIntersectii() const;

};

#endif //SIMULATOR_H
