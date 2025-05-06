#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Coordonate.h"
#include "Strada.h"
#include "Intersectie.h"
#include "Semafor.h"
#include "Utils.h"
#include "Vehicul.h"
#include "Simulator.h"

int main() {
    const int MAX_LENGTH = 1000;
    const int MAX_WIDTH = 1000;
    const int distantaSincronizare = 130;

    // crearea strazilor
    std::vector <std::shared_ptr<Strada>> strazi;
    std::vector <std::shared_ptr<Intersectie>> intersectii;
    std::vector <std::shared_ptr<Semafor>> semafoare;

    Coordonate coord1{10, 0};
    std::vector<std::pair<Coordonate, int>> limitari1 = {
        {Coordonate{10, 5}, 50},
        {Coordonate{10, 100}, 40},
        {Coordonate{10, 555}, 30}
    };

    auto Strada1 = std::make_shared<Strada>(1, "Strada Mare", coord1, Orientare::Orizontala, limitari1);
    strazi.push_back(Strada1);

    Coordonate coord2{0, 250};
    std::vector<std::pair<Coordonate, int>> limitari2 = {
        {Coordonate{25, 250}, 50},
        {Coordonate{260, 250}, 50},
        {Coordonate{700, 250}, 30}
    };

    auto Strada2 = std::make_shared<Strada>(2, "Strada Mică", coord2, Orientare::Verticala, limitari2);
    strazi.push_back(Strada2);

    // crearea intersectiilor si a semafoarelor
    for (size_t i=0; i < strazi.size(); ++i) {
        for (size_t j=i+1; j < strazi.size(); ++j) {
            auto strada1 = strazi[i];
            auto strada2 = strazi[j];

            if (seIntersecteaza (strada1, strada2)) {
                Coordonate coordIntersectie = calculeazaIntersectie(strada1, strada2);

                std::shared_ptr<Intersectie> intersectie;
                if (strada1->get_OrientareStrada() == Orientare::Verticala)
                    intersectie = std::make_shared<Intersectie>(coordIntersectie, strada1, strada2);
                else
                    intersectie = std::make_shared<Intersectie>(coordIntersectie, strada2, strada1);
                std::shared_ptr<Semafor> semafor1 = std::make_shared<Semafor>(0, 0, 0, coordIntersectie, strada1);
                std::shared_ptr<Semafor> semafor2 = std::make_shared<Semafor>(0, 0, 0, coordIntersectie, strada2);


                // Adaugă intersecția și semaforul în unordered_map
                strada1->adaugaIntersectie(coordIntersectie, intersectie);
                strada2->adaugaIntersectie(coordIntersectie, intersectie);
                strada1->adaugaSemafor(coordIntersectie, semafor1);
                strada2->adaugaSemafor(coordIntersectie, semafor2);

                intersectii.push_back(intersectie);
                semafoare.push_back(semafor1);
                semafoare.push_back(semafor2);
            }
        }
    }

    // stabilirea semafoarelor
    stabilesteSemafoare (strazi, distantaSincronizare);

    //
    return 0;
}


