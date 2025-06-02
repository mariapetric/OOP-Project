
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_set>
#include <queue>
#include <random>
#include "Coordonate.h"
#include "Strada.h"
#include "Intersectie.h"
#include "Semafor.h"
#include "Utils.h"
#include "Vehicul.h"
#include "Autobuz.h"
#include "VehiculPrioritar.h"
#include "Sens.h"

bool seIntersecteaza (const std::shared_ptr<Strada>& strada1, const std::shared_ptr<Strada>& strada2) {
    if (strada1->get_OrientareStrada() != strada2->get_OrientareStrada())
      return true;
    return false;
}

Coordonate<int> calculeazaIntersectie (const std::shared_ptr<Strada>& strada1, const std::shared_ptr<Strada>& strada2) {
    int x=-1, y=-1;
    if (strada1->get_OrientareStrada() == Orientare::Verticala && strada2->get_OrientareStrada() == Orientare::Orizontala) {
        x = strada1->get_CoordonataStart().get_x();
        y = strada2->get_CoordonataStart().get_y();
    }
    else {
        x = strada2->get_CoordonataStart().get_x();
        y = strada1->get_CoordonataStart().get_y();
    }
    return Coordonate{x, y};
}

Culoare culoare_opusa(Culoare culoareCurenta) {
    switch (culoareCurenta) {
        case Culoare::Verde:
            return Culoare::Rosu;
        case Culoare::Galben:
            return Culoare::Rosu;
        case Culoare::Rosu:
            return Culoare::Verde;
        default:
            return Culoare::Rosu;
    }


}

int distanta(const Coordonate<int>& coord1, const Coordonate<int>& coord2) {
    return std::abs(coord1.get_x() - coord2.get_x()) + std::abs(coord1.get_y() - coord2.get_y());
}


void seteazaSemafoarePeStrada (const std::shared_ptr<Strada> strada, const Culoare culoareInitiala, int distantaSincronizare) {
    auto intersectii = strada->get_IntersectiiOrdonate();

    Culoare culoareCurenta = culoareInitiala;
    Coordonate<int> ultimaPoz;

    for (size_t i = 0; i < intersectii.size(); ++i) {
        auto& [coord, intersectie] = intersectii[i];

        if (i==0 || distanta(coord, ultimaPoz) > distantaSincronizare) {
            culoareCurenta = culoare_opusa(culoareCurenta);
            ultimaPoz = coord;
        }
        auto semafor = strada->get_SemaforLaCoord(coord);
        semafor->set_Culoare(culoareCurenta);
    }

}


void stabilesteSemafoare(std::vector<std::shared_ptr<Strada>>& strazi, int distantaSincronizare) {
    std::queue<std::shared_ptr<Strada>> coada;
    std::unordered_set<int> straziProcesate;  // sa nu iau aceeasi strada de mai multe ori
    std::unordered_map<int, Culoare> semafoarePeStrada;

    // ia un semafor random pentru a începe
    auto stradaStart = strazi[0];
    coada.push(stradaStart);
    straziProcesate.insert(stradaStart->get_Id());

    // punem semaforul pe rosu
    semafoarePeStrada[stradaStart->get_Id()] = Culoare::Rosu;
    seteazaSemafoarePeStrada(stradaStart, Culoare::Rosu, distantaSincronizare);

    while (!coada.empty()) {
        auto stradaCurenta = coada.front();
        coada.pop();

        // parcurgem intersecțiile de pe strada curenta
        for (auto& [coord, intersectie] : stradaCurenta->get_IntersectiiOrdonate()) {
            auto stradaVecina = intersectie->get_CealaltaStrada(stradaCurenta);

            if (straziProcesate.find(stradaVecina->get_Id()) == straziProcesate.end()) {

                auto semaforCurent = stradaCurenta->get_SemaforLaCoord(coord);
                Culoare culoareOpusa = culoare_opusa(semaforCurent->get_Culoare());

                semafoarePeStrada[stradaVecina->get_Id()] = culoareOpusa;

                seteazaSemafoarePeStrada(stradaVecina, culoareOpusa, distantaSincronizare);

                coada.push(stradaVecina);
                straziProcesate.insert(stradaVecina->get_Id());
            }
        }
    }
}


Sens alegeDirectieRandom(Sens curent) {
    static std::default_random_engine eng{std::random_device{}()};
    // 0 = inainte , 1 = stanga, 2 = dreapta
    static std::uniform_int_distribution<int> dist(0, 2);
    int opt = dist(eng);

    switch (curent) {
        case Sens::Sus:
            if (opt == 0) return Sens::Sus;
            else {
                if (opt == 1) return Sens::Stanga;
                else return Sens::Dreapta;
            }
        case Sens::Jos:
            if (opt == 0) return Sens::Jos;
            else {
                if (opt == 1) return Sens::Dreapta;
                else return Sens::Stanga;
            }
        case Sens::Stanga:
            if (opt == 0) return Sens::Stanga;
            else {
                if (opt == 1) return Sens::Jos;
                else return Sens::Sus;
            }
        case Sens::Dreapta:
            if (opt == 0) return Sens::Dreapta;
            else {
                if (opt == 1) return Sens::Sus;
                else return Sens::Jos;
            }
    }
    return curent;
}

bool existaVehiculPrioritarAproape (const Coordonate<int>& poz, const std::vector<std::shared_ptr<Vehicul>>& vehicule) {
    for (const auto& v : vehicule) {
        if (auto vp = std::dynamic_pointer_cast<VehiculPrioritar>(v)) {
            if (distanta (poz, vp->get_PozitieVehicul() ) < 10) {
                return true;
            }
        }
    }
    return false;
}


bool vehiculInFata(
    const Vehicul& vehicul,
    const std::vector<std::shared_ptr<Vehicul>>& vehicule, float deltaSecunde
) {
    const auto& pozCurenta = vehicul.get_PozitieVehicul();
    auto sens = vehicul.get_Sens();
    auto idStrada = vehicul.get_Strada()->get_Id();

    // Prag minim de „detectie” (cel puţin 1)
    float dxPerFrame = static_cast<float>(vehicul.get_Viteza()) * deltaSecunde * 25.0f;
    int pragDetectie = static_cast<int>(std::round(dxPerFrame));
    if (pragDetectie < 1)
        pragDetectie = 1;   // măcar un pixel minim


    for (const auto& v : vehicule) {
        if (v->get_Id() == vehicul.get_Id())
            continue;
        if (v->get_Strada()->get_Id() != idStrada)
            continue;
        if (v->get_Sens() != sens)
            continue;

        const auto& pozV = v->get_PozitieVehicul();
        int dist = -1;

        switch (sens) {
            case Sens::Sus:
                if (pozV.get_x() == pozCurenta.get_x() &&
                    pozV.get_y() <= pozCurenta.get_y())
                {
                    dist = pozCurenta.get_y() - pozV.get_y();
                }
                break;

            case Sens::Jos:
                if (pozV.get_x() == pozCurenta.get_x() &&
                    pozV.get_y() >= pozCurenta.get_y())
                {
                    dist = pozV.get_y() - pozCurenta.get_y();
                }
                break;

            case Sens::Stanga:
                if (pozV.get_y() == pozCurenta.get_y() &&
                    pozV.get_x() <= pozCurenta.get_x())
                {
                    dist = pozCurenta.get_x() - pozV.get_x();
                }
                break;

            case Sens::Dreapta:
                if (pozV.get_y() == pozCurenta.get_y() &&
                    pozV.get_x() >= pozCurenta.get_x())
                {
                    dist = pozV.get_x() - pozCurenta.get_x();
                }
                break;
        }

        if (dist < 0)
            continue;

        // Dacă v[i] e exact în spatele/din faţă (dist == 0),
        // îl considerăm blocant doar dacă are ID mai mic decât vehiculul curent.
        bool acelasiLocSiIDmaiMic = (dist == 0 && v->get_Id() < vehicul.get_Id());

        if ((dist > 0 && dist <= pragDetectie) || acelasiLocSiIDmaiMic) {
            // dacă e autobuz oprit în stație chiar pe locul respectiv,
            // atunci îl ignorăm
            if (auto autob = std::dynamic_pointer_cast<Autobuz>(v)) {
                if (autob->eOpritInStatie())
                    continue;
            }
            return true;
        }
    }

    return false;
}



Sens opus(Sens s) {
    switch (s) {
        case Sens::Sus: return Sens::Jos;
        case Sens::Jos: return Sens::Sus;
        case Sens::Stanga: return Sens::Dreapta;
        case Sens::Dreapta: return Sens::Stanga;
        default: return s; // fallback de siguranță
    }
}
