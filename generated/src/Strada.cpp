//
// Created by Admin on 29.04.2025.
//

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Directie.h"
#include "Coordonate.h"
#include "Strada.h"


Strada::Strada (int id_, const std::string& nume_,
                  const Coordonate& coord_, Orientare orientare_,
                  const std::vector < std::pair<int, int> >& limitari) :
                    id{id_}, nume{nume_}, CoordonataStart{coord_},
                    OrientareStrada{orientare_}, LimitariViteza{limitari} {}

Strada::Strada (const Strada& other) : id{other.id}, nume{other.nume},
                                      CoordonataStart{other.CoordonataStart}, OrientareStrada{other.OrientareStrada},
                                      intersectii{other.intersectii}, semafoare{other.semafoare}, LimitariViteza{other.LimitariViteza} {}
Strada& Strada::operator= (const Strada& other) {
    if (this != &other) {
      id = other.id;
      nume = other.nume;
      CoordonataStart = other.CoordonataStart;
      OrientareStrada = other.OrientareStrada;
      intersectii = other.intersectii;
      semafoare = other.semafoare;
      LimitariViteza = other.LimitariViteza;
    }
    return *this;
}

std::ostream& operator<< (std::ostream& os, const Strada& obj) {
    os << obj.id << ' ' << obj.nume << ' ' << obj.CoordonataStart
    << ' ' << ((obj.OrientareStrada == Orientare::Verticala) ? "Verticala" : "Orizontala") << " Limitari: ";
    for (const auto& l : obj.LimitariViteza)
      os << "[ " << l.first << ", " << l.second << " ]";
    os << '\n';
    return os;
}

