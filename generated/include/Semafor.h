
#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <iostream>
#include <memory>
#include "Coordonate.h"

class Strada;

enum class Culoare { Verde, Galben, Rosu };

class Semafor {
     double timpVerdeRamas, timpGalbenRamas, timpRosuRamas;
     Coordonate coordonateSemafor;
     std::weak_ptr <Strada> strada;

public:
     explicit Semafor (double timpVerdeRamas, double timpGalbenRamas, double timpRosuRamas, const Coordonate& coordonateSemafor_, std::shared_ptr<Strada> strada);
     ~Semafor() = default;

     friend std::ostream& operator<< (std::ostream& os, const Semafor& obj);

     Culoare get_Culoare() const;

     void set_Culoare(Culoare culoare);
     Coordonate get_Coordonate() const;
};

#endif //SEMAFOR_H
