#include "ComportamentMasina.h"
#include "Vehicul.h"
#include "Strada.h"
#include "Semafor.h"
#include "Utils.h"
#include "Masina.h"
#include "Sens.h"
#include <memory>

ComportamentMasina::~ComportamentMasina() = default;

void ComportamentMasina::ruleaza(
    std::shared_ptr<Vehicul> self,
    const std::vector<std::shared_ptr<Vehicul>>& vehicule,
    int MAX_LENGTH, int MAX_WIDTH,
    float deltaSecunde
) {
    auto masina = std::dynamic_pointer_cast<Masina>(self);
    if (!masina) return;

    // 1. Ajustează viteza în funcție de limitările străzii
    auto strada = masina->get_Strada();
    auto pozitie = masina->get_PozitieVehicul();
    auto sens = masina->get_Sens();

    masina->set_Viteza(
        strada->get_LimitaVitezaLaPozitie(pozitie)
    );

    // 2. Oprește dacă semaforul e roșu
    auto semafor = strada->get_SemaforLaCoord(pozitie);
    if (semafor && semafor->get_Culoare() == Culoare::Rosu)
        return;

    // 3. Oprește dacă e vehicul prioritar sau coloană
    if ((semafor && semafor->get_Culoare() == Culoare::Verde &&
         existaVehiculPrioritarAproape(pozitie, vehicule)) ||
        vehiculInFata(*masina, vehicule, deltaSecunde))
    {
        return;
    }

    // 4. Dacă e aproape de intersecție, alege direcția
    const int DIST_INTERSECTIE = 10;
    if (strada->existaIntersectieLaDistanta(pozitie, DIST_INTERSECTIE, sens)) {
        Sens directieNoua = alegeDirectieRandom(sens);
        if (directieNoua != opus(sens)) {
            masina->set_orientareViitoare(directieNoua);
        }
    }

    // 5. Dacă este exact în intersecție, schimbă direcția și strada
    int delta = masina->get_Viteza() / 10;
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
                masina->set_Pozitie(c);
                break;
            }
        }

        Sens viitor = masina->get_orientareViitoare();
        if (viitor != opus(sens)) {
            masina->schimbaSensul(viitor);
            auto stradaNoua = strada->get_StradaUrmatoare(intersectieGasita, viitor, strada);
            if (stradaNoua) {
                masina->schimbaStrada(stradaNoua);
            }
        }
    }

    // 6. Dacă ajunge la marginea ecranului, întoarce
    int x = pozitie.get_x();
    int y = pozitie.get_y();
    if ((sens == Sens::Stanga && x <= 0) ||
        (sens == Sens::Dreapta && x >= MAX_LENGTH) ||
        (sens == Sens::Jos && y <= 0) ||
        (sens == Sens::Sus && y >= MAX_WIDTH)) {
        masina->schimbaSensul(opus(sens));
    }

    // 7. **Actualizează poziția cu deltaSecunde**
    masina->updatePosition(deltaSecunde, MAX_LENGTH, MAX_WIDTH);
}