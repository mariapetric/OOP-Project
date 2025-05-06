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

class Simulator {
private:
    std::vector <std::shared_ptr<Strada>> strazi;
    std::vector <std::shared_ptr<Intersectie>> intersectii;
    std::vector <std::shared_ptr<Semafor>> semafoare;
    std::vector <std::shared_ptr<Vehicul>> vehicule;
    int currentTime = 0;

public:
    void adaugaStrada (const std::shared_ptr<Strada> s);
    void adaugaIntersectie(const std::shared_ptr<Intersectie> i);
    void adaugaSemafoare (const std::shared_ptr<Semafor> s);
    void adaugaVehicul(const std::shared_ptr<Vehicul> v);
};

#endif //SIMULATOR_H
