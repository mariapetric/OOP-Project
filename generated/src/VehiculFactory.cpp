#include "VehiculFactory.h"
#include <stdexcept>

std::shared_ptr<Vehicul> VehiculFactory::creeazaVehicul(
    TipVehicul tip,
    int id,
    const Coordonate<int>& poz,
    Sens sens,
    Sens orientViitoare,
    std::shared_ptr<Strada> strada,
    int viteza
) {
    switch (tip) {
        case TipVehicul::Masina:
            return std::make_shared<Masina>(poz, sens, orientViitoare, strada, viteza);
         case TipVehicul::Autobuz:
             return std::make_shared<Autobuz>(poz, sens, orientViitoare, strada, viteza);
         case TipVehicul::Prioritar:
             return std::make_shared<VehiculPrioritar>(poz, sens, orientViitoare, strada, viteza);
        default:
            throw std::invalid_argument("TipVehicul necunoscut.");
    }
}
