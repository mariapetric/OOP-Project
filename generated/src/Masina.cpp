#include "Masina.h"
#include "Utils.h"


Masina::Masina(int id_, const Coordonate& pozitieVehicul_,
               Sens sensVehicul_, Sens orientareViitoare_,
               std::shared_ptr<Strada> strada_)
    : Vehicul(id_, pozitieVehicul_, sensVehicul_, orientareViitoare_, strada_) {}

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
//    return std::make_shared<Masina>(*this);
    return std::shared_ptr<Vehicul>(new Masina(*this));
}


std::ostream& operator<<(std::ostream& os, const Masina& obj) {
    obj.afisare(os);
    return os;
}


void Masina::ruleaza(const std::vector<std::shared_ptr<Vehicul>>& vehicule, int MAX_LENGTH, int MAX_WIDTH) {
	// vede care e limita de viteza
	viteza = strada->get_LimitaVitezaLaPozitie(pozitieVehicul);
	// daca semaforul e rosu, opreste
	auto semafor = strada->get_SemaforLaCoord(pozitieVehicul);
    if (semafor && semafor->get_Culoare() == Culoare::Rosu)
        return;
	// daca e verde si vine un prioritar, opreste
    if (semafor && semafor->get_Culoare() == Culoare::Verde && existaVehiculPrioritarAproape(pozitieVehicul, vehicule))
        return;
	// daca e un vehicul in fata, opreste
    if (vehiculInFata(*this, vehicule))
        return;

    if (strada->existaIntersectieLaDistanta(pozitieVehicul, 10, sensVehicul)) {
        // alege aleator noua directie
        Sens directieNoua = alegeDirectieRandom(sensVehicul);

        set_orientareViitoare(directieNoua);
        schimbaSensul(directieNoua);

        // gasim noua strada pe care intra vehiculul
        auto stradaNoua = strada->get_StradaUrmatoare(pozitieVehicul, directieNoua, strada);
        if (stradaNoua) {
            schimbaStrada(stradaNoua);
        }
    }

	updatePosition (MAX_LENGTH, MAX_WIDTH);
}


