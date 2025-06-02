#include "ComportamentPrioritar.h"
#include "Vehicul.h"
#include "Strada.h"
#include "Semafor.h"
#include "Utils.h"
#include "VehiculPrioritar.h"
#include "Sens.h"
#include <memory>

ComportamentPrioritar::~ComportamentPrioritar() = default;


void ComportamentPrioritar::ruleaza(std::shared_ptr<Vehicul> self,
                                     const std::vector<std::shared_ptr<Vehicul>>& vehicule,
                                     int MAX_LENGTH, int MAX_WIDTH, float deltaSecunde) {
    auto prioritar = std::dynamic_pointer_cast<VehiculPrioritar>(self);
    if (!prioritar) return;

    auto strada = prioritar->get_Strada();
    auto pozitie = prioritar->get_PozitieVehicul();
    auto sens = prioritar->get_Sens();

    // Nu respectă limitările de viteză — folosim o viteză fixă mare
    prioritar->set_Viteza(65);

    // Nu oprește la semafor și nu verifică vehicule în față

    // Dacă e aproape de intersecție, decide direcție
    const int DIST_INTERSECTIE = 10;
    if (strada->existaIntersectieLaDistanta(pozitie, DIST_INTERSECTIE, sens)) {
        Sens directieNoua = alegeDirectieRandom(sens);
        if (directieNoua != opus(sens)) {
            prioritar->set_orientareViitoare(directieNoua);
        }
    }

    // Dacă este exact în intersecție, verificăm dacă trebuie să cedeze altui vehicul prioritar
    int delta = prioritar->get_Viteza() / 10;
    if (strada->existaIntersectieLaDistanta(pozitie, delta, sens)) {
        Coordonate<int> intersectieGasita;

        for (int i = 0; i <= delta; ++i) {
            Coordonate<int> c = pozitie;
            switch (sens) {
                case Sens::Sus: c = Coordonate{c.get_x(), c.get_y() - i}; break;
                case Sens::Jos: c = Coordonate{c.get_x(), c.get_y() + i}; break;
                case Sens::Stanga: c = Coordonate{c.get_x() - i, c.get_y()}; break;
                case Sens::Dreapta: c = Coordonate{c.get_x() + i, c.get_y()}; break;
            }

            if (strada->areIntersectieLaCoordonata(c)) {
                intersectieGasita = c;
                prioritar->set_Pozitie(c);

                // Verificăm dacă există alt vehicul prioritar în intersecție
                for (const auto& v : vehicule) {
                    if (v == self) continue;
                    auto vp = std::dynamic_pointer_cast<VehiculPrioritar>(v);
                    if (vp && vp->get_PozitieVehicul() == intersectieGasita) {
                        // Dacă celălalt e și el prioritar și suntem pe orizontală, ne oprim
                        if (sens == Sens::Stanga || sens == Sens::Dreapta)
                            return;  // Celălalt (sus/jos) are prioritate
                    }
                }

                break;
            }
        }

        Sens viitor = prioritar->get_orientareViitoare();
        if (viitor != opus(sens)) {
            prioritar->schimbaSensul(viitor);
            auto stradaNoua = strada->get_StradaUrmatoare(intersectieGasita, viitor, strada);
            if (stradaNoua) {
                prioritar->schimbaStrada(stradaNoua);
            }
        }
    }

    // Se întoarce la marginea ecranului
    int x = pozitie.get_x();
    int y = pozitie.get_y();
    if ((sens == Sens::Stanga && x <= 0) ||
        (sens == Sens::Dreapta && x >= MAX_LENGTH) ||
        (sens == Sens::Jos && y <= 0) ||
        (sens == Sens::Sus && y >= MAX_WIDTH)) {
        prioritar->schimbaSensul(opus(sens));
    }

    // Actualizează poziția
    prioritar->updatePosition(deltaSecunde, MAX_LENGTH, MAX_WIDTH);
}
