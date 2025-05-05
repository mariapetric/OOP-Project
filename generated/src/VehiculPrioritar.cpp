#include "VehiculPrioritar.h"

VehiculPrioritar::VehiculPrioritar(int id_, const Coordonate& pozitieVehicul_, Sens sensVehicul_,
                                   Sens orientareViitoare_, std::shared_ptr<Strada> strada_)
    : Vehicul(id_, pozitieVehicul_, sensVehicul_, orientareViitoare_, strada_) {}

VehiculPrioritar::VehiculPrioritar(const VehiculPrioritar& other)
    : Vehicul(other) {}

VehiculPrioritar& VehiculPrioritar::operator=(const VehiculPrioritar& other) {
    if (this != &other) {
        Vehicul::operator=(other);
    }
    return *this;
}

void VehiculPrioritar::afisare(std::ostream& os) const {
    os << "[VehiculPrioritar]: " << id << " (" << pozitieVehicul.get_x()
       << ", " << pozitieVehicul.get_y() << "), Viteza: " << viteza
       << ", Sens: ";

    switch (sensVehicul) {
        case Sens::Sus: os << "Sus"; break;
        case Sens::Jos: os << "Jos"; break;
        case Sens::Stanga: os << "Stanga"; break;
        case Sens::Dreapta: os << "Dreapta"; break;
    }
    os << ", Strada ID: " << (strada ? strada->get_Id() : -1) << '\n';
}

std::shared_ptr<Vehicul> VehiculPrioritar::clone() const {
    return std::shared_ptr<Vehicul>(new VehiculPrioritar(*this));
}

std::ostream& operator<< (std::ostream& os, const VehiculPrioritar& obj) {
    obj.afisare(os);
    return os;
}


