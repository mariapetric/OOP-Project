

#include <iostream>
#include <memory>
#include "Coordonate.h"
#include "Strada.h"
#include "Semafor.h"

Semafor::Semafor (int timpVerdeRamas_, int timpGalbenRamas_, int timpRosuRamas_, const Coordonate& coordonateSemafor_, std::shared_ptr<Strada> strada) :
                timpVerdeRamas{timpVerdeRamas_}, timpGalbenRamas{timpGalbenRamas_}, timpRosuRamas{timpRosuRamas_},
                coordonateSemafor{coordonateSemafor_}, strada{strada} {}

std::ostream& operator<< (std::ostream& os, const Semafor& obj) {
    os << obj.timpVerdeRamas << ' ' << obj.timpGalbenRamas << ' ' << obj.timpRosuRamas
    << ' ' << obj.coordonateSemafor;
    if(auto strada_ptr = obj.strada.lock())
        os << ' ' << *strada_ptr << '\n';
    else os << '\n';
    return os;
}