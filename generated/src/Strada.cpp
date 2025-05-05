
#include "Strada.h"
#include "Utils.h"

Strada::Strada (int id_, const std::string& nume_,
                  const Coordonate& coord_, Orientare orientare_,
                  const std::vector < std::pair<Coordonate, int> >& limitari) :
                    id{id_}, nume{nume_}, CoordonataStart{coord_},
                    OrientareStrada{orientare_}, intersectii {}, semafoare{}, LimitariViteza{limitari} {}

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

const Coordonate& Strada::get_CoordonataStart () const {
  return CoordonataStart;
}

const Orientare& Strada::get_OrientareStrada() const {
  return OrientareStrada;
}

void Strada::adaugaIntersectie(const Coordonate& coord, std::shared_ptr<Intersectie> intersectie) {
  intersectii[coord] = intersectie;
}

void Strada::adaugaSemafor(const Coordonate& coord, std::shared_ptr<Semafor> semafor) {
  semafoare[coord] = semafor;
}

std::vector<std::pair<Coordonate, std::shared_ptr<Intersectie>>> Strada::get_IntersectiiOrdonate() const {
  std::vector<std::pair<Coordonate, std::shared_ptr<Intersectie>>> intersectiiOrdonate;

  for (const auto& [coord, intersectie] : intersectii) {
    if (auto sp = intersectie.lock()) {
      intersectiiOrdonate.push_back({coord, sp});
    }
  }

  if (OrientareStrada == Orientare::Orizontala) {
    std::sort(intersectiiOrdonate.begin(), intersectiiOrdonate.end(),
        [](const auto& a, const auto& b) {
            return a.first.get_x() < b.first.get_x(); // sortare dupa x
        });
  } else {
    std::sort(intersectiiOrdonate.begin(), intersectiiOrdonate.end(),
        [](const auto& a, const auto& b) {
            return a.first.get_y() < b.first.get_y(); // sortare dupa y
        });
  }

  return intersectiiOrdonate;
}


std::vector < std::pair<Coordonate, int> > Strada::get_LimitariVitezaSorted () const {

  std::vector < std::pair<Coordonate, int> > limiteOrdonate;
  for (const auto& [coord, Viteza] : LimitariViteza) {
    limiteOrdonate.push_back({coord, Viteza});
  }

  if (OrientareStrada == Orientare::Orizontala) {
    std::sort( limiteOrdonate.begin(), limiteOrdonate.end(),
    [](const auto& a, const auto& b) {
      return a.first.get_x() < b.first.get_x();
    } );
  }

  else {
    std::sort( limiteOrdonate.begin(), limiteOrdonate.end(),
    [](const auto& a, const auto& b) {
      return a.first.get_y() < b.first.get_y();
    } );
  }
  return limiteOrdonate;
}


std::shared_ptr<Semafor> Strada::get_SemaforLaCoord(const Coordonate& coord) const {
  auto it = semafoare.find(coord);
  if (it != semafoare.end()) {
    return it->second;
  }
  return nullptr;
}

int Strada::get_Id () const {
  return id;
}

int Strada::get_LimitaVitezaLaPozitie(const Coordonate& poz) const {
  for (const auto& [coord, viteza] : LimitariViteza) {
    if ( distanta(poz, coord) < 100 )
      return viteza;
  }
  return 50; //zona fara limitare
}

std::shared_ptr<Semafor> Strada::get_SemaforLaPozitie(const Coordonate& poz) const {
  for (const auto& [coord, semafor] : semafoare) {
    if ( distanta(poz, coord) < 100 ) {
      return semafor;
    }
  }
  return nullptr;
}


bool Strada::existaIntersectieLaDistanta(const Coordonate& poz, int distantaMax, Sens sensVehicul) const {
  auto intersectiiOrdonate = get_IntersectiiOrdonate();

  for (const auto& [coordIntersectie, intersectie] : intersectiiOrdonate) {
    if (OrientareStrada == Orientare::Orizontala) {
      if (sensVehicul == Sens::Dreapta && coordIntersectie.get_x() > poz.get_x() &&
          coordIntersectie.get_x() - poz.get_x() <= distantaMax)
        return true;

      if (sensVehicul == Sens::Stanga && coordIntersectie.get_x() < poz.get_x() &&
          poz.get_x() - coordIntersectie.get_x() <= distantaMax)
        return true;

    } else { // Verticala
      if (sensVehicul == Sens::Sus && coordIntersectie.get_y() > poz.get_y() &&
          coordIntersectie.get_y() - poz.get_y() <= distantaMax)
        return true;

      if (sensVehicul == Sens::Jos && coordIntersectie.get_y() < poz.get_y() &&
          poz.get_y() - coordIntersectie.get_y() <= distantaMax)
        return true;
    }
  }

  return false;
}


std::shared_ptr<Strada> Strada::get_StradaUrmatoare(const Coordonate& poz, Sens directieNoua, std::shared_ptr<Strada> stradaAct) const {
  std::shared_ptr<Strada> stradaUrmatoare = nullptr;
  int distantaMinima = std::numeric_limits<int>::max();

  //parcurgem intersectiile
  for (const auto& [coord, intersectieWeak] : intersectii) {
    if (auto intersectie = intersectieWeak.lock()) {

      if (intersectie->get_StradaVerticala() != stradaAct && intersectie->get_StradaOrizontala() != stradaAct)
        continue;

      int distantaCurenta = 0;

      if (OrientareStrada == Orientare::Orizontala) {
        if (directieNoua == Sens::Dreapta && coord.get_x() > poz.get_x()) {
          distantaCurenta = coord.get_x() - poz.get_x();
        } else if (directieNoua == Sens::Stanga && coord.get_x() < poz.get_x()) {
          distantaCurenta = poz.get_x() - coord.get_x();
        }
      } else { // verticala
        if (directieNoua == Sens::Sus && coord.get_y() > poz.get_y()) {
          distantaCurenta = coord.get_y() - poz.get_y();
        } else if (directieNoua == Sens::Jos && coord.get_y() < poz.get_y()) {
          distantaCurenta = poz.get_y() - coord.get_y();
        }
      }

      if (distantaCurenta < distantaMinima) {
        distantaMinima = distantaCurenta;
        stradaUrmatoare = intersectie->get_CealaltaStrada(stradaAct);
      }
    }
  }

  return stradaUrmatoare;
}






