#include "Vehicul.h"

int Vehicul::global_id = 1;

Vehicul::Vehicul(const Coordonate<int>& pozitieVehicul_, Sens sensVehicul_, Sens orientareViitoare_, const std::shared_ptr<Strada>& strada_, int viteza_) :
    id{global_id++}, pozitieVehicul{pozitieVehicul_}, sensVehicul{sensVehicul_}, orientareViitoare{orientareViitoare_}, strada{strada_}, viteza{viteza_}{

    if (!strada) {
        throw InvalidStartPositionException("Vehiculul nu poate fi plasat pe o strada invalidă.");
    }

    if (pozitieVehicul_.get_x() < 0 || pozitieVehicul_.get_x() > MAX_LENGTH || pozitieVehicul_.get_y() < 0 || pozitieVehicul_.get_y() > MAX_WIDTH) {
        throw InvalidStartPositionException("Pozitia vehiculului este invalida: in afara limitelor ecranului..");
    }
}


Vehicul::Vehicul(const Vehicul& other) : std::enable_shared_from_this<Vehicul>(other),
        id{other.id}, pozitieVehicul{other.pozitieVehicul},
        sensVehicul{other.sensVehicul}, orientareViitoare{other.orientareViitoare}, strada{other.strada}, viteza{other.viteza} {}

Vehicul& Vehicul::operator=(const Vehicul& other) {
    if (this != &other) {
        id = other.id;
        pozitieVehicul = other.pozitieVehicul;
        sensVehicul = other.sensVehicul;
        orientareViitoare = other.orientareViitoare;
        strada = other.strada;
        viteza = other.viteza;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Vehicul& obj) {
    obj.afisare(os);
    return os;
}

Sens Vehicul::get_Sens() const {
  return sensVehicul;
}

Coordonate<int> Vehicul::get_PozitieVehicul() const {
  return pozitieVehicul;
}

std::shared_ptr<Strada> Vehicul::get_Strada() const {
  return strada;
}

int Vehicul::get_Id() const {
  return id;
}

void Vehicul::set_orientareViitoare (Sens sensVehicul_) {
	orientareViitoare = sensVehicul_;
}

Sens Vehicul::get_orientareViitoare() const {
    return orientareViitoare;
}

void Vehicul::set_Viteza(int viteza_) {
    viteza = viteza_;
}

int Vehicul::get_Viteza() const {
    return viteza;
}

void Vehicul::set_Pozitie(Coordonate<int> poz) {
    pozitieVehicul = poz;
}

void Vehicul::updatePosition(float deltaSecunde, int MAX_LENGTH, int MAX_WIDTH) {
    float dx = 0.f, dy = 0.f;
    switch (sensVehicul) {
        case Sens::Sus:
            dy = static_cast<float>(viteza) * deltaSecunde*2500.0f;
        break;
        case Sens::Jos:
            dy =  -static_cast<float>(viteza) * deltaSecunde*2500.0f;
        break;
        case Sens::Dreapta:
            dx = static_cast<float>(viteza) * deltaSecunde*2500.0f;
        break;
        case Sens::Stanga:
            dx = -static_cast<float>(viteza) * deltaSecunde*2500.0f;
        break;
    }

    // calculează noile coordonate ca float
    float newX = static_cast<float>(pozitieVehicul.get_x()) + dx;
    float newY = static_cast<float>(pozitieVehicul.get_y()) + dy;

    // păstrează-le înapoi ca int (sau poți schimba Coordonate<int> în Coordonate<float>)
    pozitieVehicul.set_x(static_cast<int>(std::round(newX)));
    pozitieVehicul.set_y(static_cast<int>(std::round(newY)));

    // Dacă treci de marginea ecranului, corectează și inversează sensul:
    if (pozitieVehicul.get_x() < 0)
        pozitieVehicul.set_x(0);
    else if (pozitieVehicul.get_x() > MAX_LENGTH)
        pozitieVehicul.set_x(MAX_LENGTH);

    if (pozitieVehicul.get_y() < 0)
        pozitieVehicul.set_y(0);
    else if (pozitieVehicul.get_y() > MAX_WIDTH)
        pozitieVehicul.set_y(MAX_WIDTH);
}



void Vehicul::schimbaSensul(Sens nouSens) {
        sensVehicul = nouSens;
        orientareViitoare = nouSens;
    }

void Vehicul::schimbaStrada(std::shared_ptr<Strada> stradaNoua) {
	strada = stradaNoua;
}

bool Vehicul::eOpritInStatie() { return false; }

void Vehicul::setStrategieRulare (std::shared_ptr<ComportamentRulare> strategieRulare_) {
    strategieRulare = strategieRulare_;
}
void Vehicul::ruleaza (const std::vector<std::shared_ptr<Vehicul>>& vehicule,
    int MAX_LENGTH, int MAX_WIDTH, float deltaSecunde) {
    if (strategieRulare)
        strategieRulare->ruleaza(shared_from_this(), vehicule, MAX_LENGTH, MAX_WIDTH, deltaSecunde);
}



