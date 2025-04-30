
#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <iostream>
#include <memory>
#include "Coordonate.h"

class Strada;

class Semafor {
     int timpVerdeRamas, timpGalbenRamas, timpRosuRamas;
     Coordonate coordonateSemafor;
     std::weak_ptr <Strada> strada;

public:
     explicit Semafor (int timpVerdeRamas, int timpGalbenRamas, int timpRosuRamas, const Coordonate& coordonateSemafor_, std::shared_ptr<Strada> strada);
     ~Semafor() = default;

     friend std::ostream& operator<< (std::ostream& os, const Semafor& obj);

};

#endif //SEMAFOR_H
