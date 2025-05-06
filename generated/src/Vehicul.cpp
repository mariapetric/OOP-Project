#include "Vehicul.h"

Vehicul::Vehicul(int id_, const Coordonate& pozitieVehicul_, Sens sensVehicul_, Sens orientareViitoare_, std::shared_ptr<Strada> strada_) :
    id{id_}, viteza{50}, pozitieVehicul{pozitieVehicul_}, sensVehicul{sensVehicul_}, orientareViitoare{orientareViitoare_}, strada{strada_} {

    if (!strada) {
        throw InvalidStartPositionException("Vehiculul nu poate fi plasat pe o strada invalidă.");
    }

    if (pozitieVehicul_.get_x() < 0 || pozitieVehicul_.get_x() > MAX_LENGTH || pozitieVehicul_.get_y() < 0 || pozitieVehicul_.get_y() > MAX_WIDTH) {
        throw InvalidStartPositionException("Pozitia vehiculului este invalida: in afara limitelor ecranului..");
    }
}


Vehicul::Vehicul(const Vehicul& other) : id{other.id}, viteza{other.viteza}, pozitieVehicul{other.pozitieVehicul},
                                          sensVehicul{other.sensVehicul}, orientareViitoare{other.orientareViitoare}, strada{other.strada} {}

Vehicul& Vehicul::operator=(const Vehicul& other) {
    if (this != &other) {
        id = other.id;
        viteza = other.viteza;
        pozitieVehicul = other.pozitieVehicul;
        sensVehicul = other.sensVehicul;
        orientareViitoare = other.orientareViitoare;
        strada = other.strada;
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

Coordonate Vehicul::get_PozitieVehicul() const {
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

void Vehicul::updatePosition(int MAX_LENGTH, int MAX_WIDTH) {
	switch (sensVehicul) {
		case Sens::Sus :
        	pozitieVehicul.set_y (pozitieVehicul.get_y() + viteza/10 );
            break;
        case Sens::Jos:
        	pozitieVehicul.set_y (pozitieVehicul.get_y() - viteza/10 );
            break;
        case Sens::Stanga:
        	pozitieVehicul.set_x (pozitieVehicul.get_x() - viteza/10 );
            break;
        case Sens::Dreapta:
        	pozitieVehicul.set_x (pozitieVehicul.get_x() + viteza/10 );
	}

    if (pozitieVehicul.get_x() >= MAX_LENGTH) {
		pozitieVehicul.set_x (MAX_LENGTH);
        sensVehicul = Sens::Stanga;
    }
    else if (pozitieVehicul.get_x() <= 0) {
      pozitieVehicul.set_x (0);
      sensVehicul = Sens::Dreapta;
    }
    if (pozitieVehicul.get_y() >= MAX_WIDTH) {
		pozitieVehicul.set_y (MAX_WIDTH);
        sensVehicul = Sens::Jos;
    }
    else if (pozitieVehicul.get_y() <= 0) {
      pozitieVehicul.set_y (0);
      sensVehicul = Sens::Sus;
    }
}

void Vehicul::schimbaSensul(Sens nouSens) {
        sensVehicul = nouSens;
        orientareViitoare = nouSens;
    }

void Vehicul::schimbaStrada(std::shared_ptr<Strada> stradaNoua) {
	strada = stradaNoua;
}

bool Vehicul::eOpritInStatie() const { return false; }





