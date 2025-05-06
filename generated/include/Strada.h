
#ifndef STRADA_H
#define STRADA_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "Directie.h"
#include "Coordonate.h"
#include "Sens.h"
#include "TrafficSimulationException.h"

class Vehicul;

class Intersectie;
class Semafor;
enum class Orientare { Verticala, Orizontala };

class Strada {
  int id;
  std::string nume;
  Coordonate CoordonataStart;
  Orientare OrientareStrada;
  std::unordered_map < Coordonate, std::weak_ptr<Intersectie> > intersectii;
  std::unordered_map < Coordonate, std::shared_ptr<Semafor> > semafoare;
  std::vector < std::pair<Coordonate, int> > LimitariViteza; // (coordonata, viteza)

public:
  explicit Strada (int id_, const std::string& nume_, const Coordonate& coord_, Orientare orientare_,
                  const std::vector < std::pair<Coordonate, int> >& limitari);
  ~Strada() = default;
  Strada (const Strada& other);
  Strada& operator= (const Strada& other);

  friend std::ostream& operator<< (std::ostream& os, const Strada& obj);

  const Coordonate& get_CoordonataStart () const;
  const Orientare& get_OrientareStrada () const;

  void adaugaIntersectie (const Coordonate& coord, std::shared_ptr<Intersectie> intersectie);
  void adaugaSemafor (const Coordonate& coord, std::shared_ptr<Semafor> semafor);

  std::vector <std::pair <Coordonate, std::shared_ptr<Intersectie>>> get_IntersectiiOrdonate() const;

    std::shared_ptr<Semafor> get_SemaforLaCoord(const Coordonate& coord) const;
    int get_Id () const;

    std::vector < std::pair<Coordonate, int> > get_LimitariVitezaSorted () const;
    int get_LimitaVitezaLaPozitie(const Coordonate& poz) const;
    std::shared_ptr<Semafor> get_SemaforLaPozitie(const Coordonate& poz) const;
    bool existaIntersectieLaDistanta(const Coordonate& poz, int distantaMax, Sens sensVehicul) const;
    std::shared_ptr<Strada> get_StradaUrmatoare(const Coordonate& poz, Sens directieNoua, std::shared_ptr<Strada> stradaAct) const;


};

#endif //STRADA_H
