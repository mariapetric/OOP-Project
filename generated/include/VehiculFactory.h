#ifndef VEHICUL_FACTORY_H
#define VEHICUL_FACTORY_H

#include <memory>
#include "Vehicul.h"
#include "Masina.h"
#include "Autobuz.h"
#include "VehiculPrioritar.h"

enum class TipVehicul {
    Masina,
    Autobuz,
    Prioritar
};

class VehiculFactory {
public:
    static std::shared_ptr<Vehicul> creeazaVehicul(
        TipVehicul tip,
        int id,
        const Coordonate<int>& poz,
        Sens sens,
        Sens orientViitoare,
        std::shared_ptr<Strada> strada,
        int viteza = 70
    );
};

#endif
