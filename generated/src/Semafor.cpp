

#include <iostream>
#include <memory>
#include "Coordonate.h"
#include "Strada.h"
#include "Semafor.h"

Semafor::Semafor (double timpVerdeRamas_, double timpGalbenRamas_, double timpRosuRamas_, const Coordonate<int>& coordonateSemafor_, std::shared_ptr<Strada> strada) :
                timpVerdeRamas{timpVerdeRamas_}, timpGalbenRamas{timpGalbenRamas_}, timpRosuRamas{timpRosuRamas_},
                coordonateSemafor{coordonateSemafor_}, strada{strada} {}

std::ostream& operator<< (std::ostream& os, const Semafor& obj) {
    if (obj.timpVerdeRamas > 0) {
        os << "Verde (" << obj.timpVerdeRamas << " secunde)";
    } else if (obj.timpGalbenRamas > 0) {
        os << "Galben (" << obj.timpGalbenRamas << " secunde)";
    } else if (obj.timpRosuRamas > 0) {
        os << "Rosu (" << obj.timpRosuRamas << " secunde)";
    }
    os << obj.coordonateSemafor;
    if(auto strada_ptr = obj.strada.lock())
        os << ' ' << *strada_ptr << '\n';
    else os << '\n';
    return os;
}

Coordonate<int> Semafor::get_Coordonate() const {
    return coordonateSemafor;
}

Culoare Semafor::get_Culoare() const {
    if (timpVerdeRamas > 0.0) {
        return Culoare::Verde;
    } else if (timpGalbenRamas > 0.0) {
        return Culoare::Galben;
    } else if (timpRosuRamas > 0.0) {
        return Culoare::Rosu;
    }
    return Culoare::Rosu;
}

void Semafor::set_Culoare(Culoare culoare) {
    switch (culoare) {
        case Culoare::Verde:
            timpVerdeRamas = 10.0;
            timpGalbenRamas = 0.0;
            timpRosuRamas = 0.0;
            break;
        case Culoare::Galben:
            timpVerdeRamas = 0.0;
            timpGalbenRamas = 2.0;
            timpRosuRamas = 0.0;
            break;
        case Culoare::Rosu:
            timpVerdeRamas = 0.0;
            timpGalbenRamas = 0.0;
            timpRosuRamas = 12.0;
            break;
        default:
            throw std::invalid_argument("Culoare necunoscută în setCuloare.");
    }
}

void Semafor::update(double deltaTimp) {
    if (timpVerdeRamas > 0) {
        timpVerdeRamas -= deltaTimp;
        if (timpVerdeRamas <= 0) {
            set_Culoare(Culoare::Galben);
        }
    } else if (timpGalbenRamas > 0) {
        timpGalbenRamas -= deltaTimp;
        if (timpGalbenRamas <= 0) {
            set_Culoare(Culoare::Rosu);
        }
    } else if (timpRosuRamas > 0) {
        timpRosuRamas -= deltaTimp;
        if (timpRosuRamas <= 0) {
            set_Culoare(Culoare::Verde);
        }
    }
}

std::shared_ptr<Strada> Semafor::getStrada() const {
    return strada.lock(); // întoarce un shared_ptr (poate fi nullptr dacă obiectul a fost distrus)
}








