#include "Autobuz.h"
#include "ComportamentAutobuz.h"

Autobuz::Autobuz(const Coordonate<int>& pozitieVehicul_,
                 Sens sensVehicul_, Sens orientareViitoare_,
                 const std::shared_ptr<Strada>& strada_, int viteza_, float distantaParcursa_)
    : Vehicul(pozitieVehicul_, sensVehicul_, orientareViitoare_, strada_, viteza_),
      distantaParcursa(distantaParcursa_) {
    setStrategieRulare(std::make_shared<ComportamentAutobuz>());
}

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
    if (distantaParcursa > 0 && distantaParcursa >= 10.0f) {
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

bool Autobuz::eOpritInStatie() {
    if (distantaParcursa >= 100.0f) {
        distantaParcursa -= 100.0f; // păstrează excesul (dacă ai făcut 112 → rămâi cu 12)
        return true;
    }
    return false;
}

void Autobuz::updatePosition(float deltaSecunde, int MAX_LENGTH, int MAX_WIDTH) {
    float dx = 0.f, dy = 0.f;
    switch (sensVehicul) {
        case Sens::Sus:
            dy =  static_cast<float>(viteza) * deltaSecunde * 2500.0f;
        break;
        case Sens::Jos:
            dy = -static_cast<float>(viteza) * deltaSecunde * 2500.0f;
        break;
        case Sens::Dreapta:
            dx =  static_cast<float>(viteza) * deltaSecunde * 2500.0f;
        break;
        case Sens::Stanga:
            dx = -static_cast<float>(viteza) * deltaSecunde * 2500.0f;
        break;
    }

    // 2.1. Calculez noile coordonate ca float
    float newX = static_cast<float>(pozitieVehicul.get_x()) + dx;
    float newY = static_cast<float>(pozitieVehicul.get_y()) + dy;

    // 2.2. Convertesc în int (round) pentru pozitiaVehicul
    pozitieVehicul.set_x(static_cast<int>(std::round(newX)));
    pozitieVehicul.set_y(static_cast<int>(std::round(newY)));

    // 2.3. Acum acumulez distanța parcursă (sub pixelii) ca sumă de |dx| + |dy|
    distantaParcursa += std::fabs(dx) + std::fabs(dy);

    // 2.4. Clamping pe marginea ecranului (dar nu schimbi sens aici, gestionați în comportament)
    if (pozitieVehicul.get_x() < 0)
        pozitieVehicul.set_x(0);
    else if (pozitieVehicul.get_x() > MAX_LENGTH)
        pozitieVehicul.set_x(MAX_LENGTH);

    if (pozitieVehicul.get_y() < 0)
        pozitieVehicul.set_y(0);
    else if (pozitieVehicul.get_y() > MAX_WIDTH)
        pozitieVehicul.set_y(MAX_WIDTH);
}

int Autobuz::get_timpStationare() {
    return timpStationare;
}

void Autobuz::set_timpStationare(int timp_) {
    timpStationare = timp_;
}