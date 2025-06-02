#include "Simulator.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void Simulator::adaugaStrada (const std::shared_ptr<Strada> s) {
  strazi.push_back(s);
}

void Simulator::adaugaIntersectie(const std::shared_ptr<Intersectie> i) {
  intersectii.push_back(i);
}

void Simulator::adaugaSemafoare (const std::shared_ptr<Semafor> s) {
  semafoare.push_back(s);
}

void Simulator::adaugaVehicul(const std::shared_ptr<Vehicul> v) {
  vehicule.push_back(v);
}

void Simulator::simuleazaTimp(double deltaSecunde) {
  // 1) Actualizează semafoarele cu deltaSecunde
  for (auto& semafor : semafoare) {
    if (semafor) semafor->update(deltaSecunde);
  }

  // 2) Rulează comportamentul fiecărui vehicul, folosind exact același deltaSecunde
  for (auto& v : vehicule) {
    if (v)
      v->ruleaza(vehicule, 1000, 1000, deltaSecunde);
  }

  // 3) Avansăm timpul intern (dacă îl mai folosești în simulare)
  currentTime += deltaSecunde;
}


int Simulator::getTimpCurent() const {
  return currentTime;
}

const std::vector<std::shared_ptr<Vehicul>>& Simulator::getVehicule() const {
  return vehicule;
}
const std::vector <std::shared_ptr<Strada>>& Simulator::getStrazi() const {
  return strazi;
}
const std::vector <std::shared_ptr<Semafor>>& Simulator::getSemafoare() const {
  return semafoare;
}
const std::vector <std::shared_ptr<Intersectie>>& Simulator::getIntersectii() const {
  return intersectii;
}