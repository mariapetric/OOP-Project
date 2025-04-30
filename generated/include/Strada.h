
#ifndef STRADA_H
#define STRADA_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Directie.h"
#include "Coordonate.h"

class Intersectie;
class Semafor;
enum class Orientare { Verticala, Orizontala };

class Strada {
  int id;
  std::string nume;
  Coordonate CoordonataStart;
  Orientare OrientareStrada;
  std::vector < std::weak_ptr<Intersectie> > intersectii;
  std::vector < std::shared_ptr<Semafor> > semafoare;
  std::vector < std::pair<int, int> > LimitariViteza; // (coordonata, viteza)

public:
  explicit Strada (int id_, const std::string& nume_, const Coordonate& coord_, Orientare orientare_,
                  const std::vector < std::pair<int, int> >& limitari);
  ~Strada() = default;
  Strada (const Strada& other);
  Strada& operator= (const Strada& other);

  friend std::ostream& operator<< (std::ostream& os, const Strada& obj);
};

#endif //STRADA_H
