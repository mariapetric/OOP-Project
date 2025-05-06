#include "Simulator.h"
#include <iostream>
#include <vector>

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