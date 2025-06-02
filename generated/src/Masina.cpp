#include "Masina.h"
#include "Utils.h"
#include "ComportamentMasina.h"

Masina::Masina(const Coordonate<int>& pozitieVehicul_,
               Sens sensVehicul_, Sens orientareViitoare_,
               const std::shared_ptr<Strada>& strada_, int viteza_)
    : Vehicul(pozitieVehicul_, sensVehicul_, orientareViitoare_, strada_, viteza_) {
    setStrategieRulare(std::make_shared<ComportamentMasina>());
}

Masina::Masina (const Masina& other) : Vehicul(other) {}

Masina& Masina::operator= (const Masina& other) {
    if (this != &other) {
        Vehicul::operator=(other);
    }
    return *this;
}


void Masina::afisare(std::ostream& os) const {
    os << id << " (" << pozitieVehicul.get_x() << ", " << pozitieVehicul.get_y() << ") "
       << "Viteza: " << viteza << ", Sens: ";

    switch (sensVehicul) {
        case Sens::Sus: os << "Sus"; break;
        case Sens::Jos: os << "Jos"; break;
        case Sens::Stanga: os << "Stanga"; break;
        case Sens::Dreapta: os << "Dreapta"; break;
    }

    os << ", Strada: " << (strada ? strada->get_Id() : -1) << '\n';
}

std::shared_ptr<Vehicul> Masina::clone() const {
    return std::make_shared<Masina>(*this);
    //return std::shared_ptr<Vehicul>(new Masina(*this));
}


std::ostream& operator<<(std::ostream& os, const Masina& obj) {
    obj.afisare(os);
    return os;
}





