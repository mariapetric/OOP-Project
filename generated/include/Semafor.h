
#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <iostream>
#include <memory>
#include "Coordonate.h"

class Strada;

enum class Culoare { Verde, Galben, Rosu };

class Semafor {
     double timpVerdeRamas, timpGalbenRamas, timpRosuRamas;
     Coordonate<int> coordonateSemafor;
     std::weak_ptr <Strada> strada;

public:
     explicit Semafor (double timpVerdeRamas, double timpGalbenRamas, double timpRosuRamas, const Coordonate<int>& coordonateSemafor_, std::shared_ptr<Strada> strada);
     ~Semafor() = default;

     friend std::ostream& operator<< (std::ostream& os, const Semafor& obj);

     Culoare get_Culoare() const;

     void set_Culoare(Culoare culoare);
     Coordonate<int> get_Coordonate() const;
     void update(double deltaTimp);
     std::shared_ptr<Strada> getStrada() const;
};

#endif //SEMAFOR_H
