#include "Autobuz.h"

Autobuz::Autobuz(int id_, const Coordonate& pozitieVehicul_,
                 Sens sensVehicul_, Sens orientareViitoare_,
                 std::shared_ptr<Strada> strada_, int distantaParcursa_)
    : Vehicul(id_, pozitieVehicul_, sensVehicul_, orientareViitoare_, strada_),
      distantaParcursa(distantaParcursa_) {}

Autobuz::Autobuz(const Autobuz& other)
    : Vehicul(other), distantaParcursa(other.distantaParcursa) {}

Autobuz& Autobuz::operator=(const Autobuz& other) {
    if (this != &other) {
        Vehicul::operator=(other);
        distantaParcursa = other.distantaParcursa;
    }
    return *this;
}

void Autobuz::afisare(std::ostream& os) const {
    os << "[Autobuz] ID: " << id << ", Pozitie: (" << pozitieVehicul.get_x()
       << ", " << pozitieVehicul.get_y() << "), Viteza: " << viteza
       << ", Sens: ";

    switch (sensVehicul) {
        case Sens::Sus: os << "Sus"; break;
        case Sens::Jos: os << "Jos"; break;
        case Sens::Stanga: os << "Stanga"; break;
        case Sens::Dreapta: os << "Dreapta"; break;
    }

    os << ", Strada ID: " << (strada ? strada->get_Id() : -1)
       << ", Distanta parcursa: " << distantaParcursa << "m";

    // Oprire în stație la fiecare 100m, dar nu în intersecții (decizia e la nivel superior)
    if (distantaParcursa > 0 && distantaParcursa % 100 == 0) {
        os << " [Oprire in statie]";
    }
    os << '\n';
}

std::shared_ptr<Vehicul> Autobuz::clone() const {
    return std::shared_ptr<Vehicul>(new Autobuz(*this));
}

std::ostream& operator<<(std::ostream& os, const Autobuz& obj) {
    obj.afisare(os);
    return os;
}

bool Autobuz::eOpritInStatie() const {
	if (distantaParcursa >= 100)
    	return true;
    return false;
}



