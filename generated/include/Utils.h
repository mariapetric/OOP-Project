#ifndef UTILS_H
#define UTILS_H

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
class Strada;
class Masina;

bool seIntersecteaza (const std::shared_ptr<Strada>& strada1, const std::shared_ptr<Strada>& strada2);

Coordonate<int> calculeazaIntersectie (const std::shared_ptr<Strada>& strada1, const std::shared_ptr<Strada>& strada2);

int distanta(const Coordonate<int>& coord1, const Coordonate<int>& coord2);
Culoare culoare_opusa(Culoare culoareCurenta);
void seteazaSemafoarePeStrada (const std::shared_ptr<Strada> strada, const Culoare culoareInitiala, int distantaSincronizare);
void stabilesteSemafoare(std::vector<std::shared_ptr<Strada>>& strazi, int distantaSincronizare);
Sens alegeDirectieRandom(Sens curent);
bool existaVehiculPrioritarAproape (const Coordonate<int>& poz, const std::vector<std::shared_ptr<Vehicul>>& vehicule);
bool vehiculInFata(const Vehicul& vehicul, const std::vector<std::shared_ptr<Vehicul>>& vehicule, float deltaSecunde);
Sens opus(Sens s);

#endif //UTILS_H


