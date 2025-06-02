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
#include "SimulatorGrafica.h"

int main() {
    const int MAX_LENGTH = 1000;
    const int MAX_WIDTH = 1000;
    const int distantaSincronizare = 130;
    Simulator& sim = Simulator::getInstance();

    // crearea strazilor
    std::vector <std::shared_ptr<Strada>> strazi;
    std::vector <std::shared_ptr<Intersectie>> intersectii;
    std::vector <std::shared_ptr<Semafor>> semafoare;

    Coordonate coord1{100, 0};
    std::vector<std::pair<Coordonate<int>, int>> limitari1 = {
        {Coordonate{100, 5}, 50},
        {Coordonate{100, 100}, 40},
        {Coordonate{100, 555}, 30}
    };

    auto Strada1 = std::make_shared<Strada>(1, "Strada Mare", coord1, Orientare::Verticala, limitari1);
    strazi.push_back(Strada1);

    Coordonate coord2{0, 150};
    std::vector<std::pair<Coordonate<int>, int>> limitari2 = {
        {Coordonate{25, 150}, 50},
        {Coordonate{260, 150}, 50},
        {Coordonate{700, 150}, 30}
    };

    auto Strada2 = std::make_shared<Strada>(2, "Strada Mică", coord2, Orientare::Orizontala, limitari2);
    strazi.push_back(Strada2);

    Coordonate coord{400, 0};
    std::vector<std::pair<Coordonate<int>, int>> limitari = {
        {Coordonate{400, 150}, 50},
        {Coordonate{400, 550}, 50},
        {Coordonate{400, 850}, 30}
    };

    auto Stradaa = std::make_shared<Strada>(3, "Strada Mică", coord, Orientare::Verticala, limitari);
    strazi.push_back(Stradaa);

    // crearea intersectiilor si a semafoarelor
    for (size_t i=0; i < strazi.size(); ++i) {
        for (size_t j=i+1; j < strazi.size(); ++j) {
            auto strada1 = strazi[i];
            auto strada2 = strazi[j];

            if (seIntersecteaza (strada1, strada2)) {
                std::cout << "inatlnireee\n";
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

    // Creează o mașină pe acea stradă
    auto v = std::make_shared<Masina>(Coordonate{100, 0}, Sens::Sus, Sens::Sus, Strada1, 70);
    auto v2 = std::make_shared<Autobuz>(Coordonate{100, 0}, Sens::Sus, Sens::Sus, Strada1, 70);
    auto v3 = std::make_shared<VehiculPrioritar>(Coordonate{100, 0}, Sens::Sus, Sens::Sus, Strada1, 70);
    auto x = std::make_shared<Autobuz> (Coordonate{100, ::MAX_WIDTH}, Sens::Jos, Sens::Jos, Strada1, 70, 0);

    // Vector de vehicule
    std::vector<std::shared_ptr<Vehicul>> vehicule = {v, v2, v3, x};

    // Testează rularea
    //v->ruleaza(vehicule, 800, 600);

    // Configurează simulatorul
    for (auto& x: vehicule)
        sim.adaugaVehicul(x);

    for (auto& x: strazi)
        sim.adaugaStrada(x);

    for (auto& x: intersectii)
        sim.adaugaIntersectie(x);

    for (auto& x: semafoare)
        sim.adaugaSemafoare(x);


    // Rulare simulare: 20 pași, câte 0.5 secunde fiecare
    // sim.simuleazaTimp(50, 0.5);
    //
    std::cout << sim.getVehicule().size() << '\n';
    std::cout << "Nr. strazi in Simulator: " << sim.getStrazi().size() << "\n";
    std::cout << "Nr. vehicule in Simulator: " << sim.getVehicule().size() << "\n";
    std::cout << "Nr. semafoare in Simulator: " << sim.getSemafoare().size() << "\n";
    std::cout << "Nr. intersectii in Simulator: " << sim.getIntersectii().size() << "\n";

    SimulatorGrafica grafica(sim, 1000, 1000);
    grafica.ruleaza();
    return 0;
}
