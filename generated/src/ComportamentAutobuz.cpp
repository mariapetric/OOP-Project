#include "ComportamentAutobuz.h"
#include "Autobuz.h"
#include "Strada.h"
#include "Semafor.h"
#include "Utils.h"
#include "Sens.h"

ComportamentAutobuz::~ComportamentAutobuz() = default;


void ComportamentAutobuz::ruleaza(
    std::shared_ptr<Vehicul> self,
    const std::vector<std::shared_ptr<Vehicul>>& vehicule,
    int MAX_LENGTH, int MAX_WIDTH,
    float deltaSecunde
) {
    auto autobuz = std::dynamic_pointer_cast<Autobuz>(self);
    if (!autobuz) return;

    // 1. Ajustează viteza în funcție de limitările străzii
    auto strada = autobuz->get_Strada();
    auto pozitie = autobuz->get_PozitieVehicul();
    auto sens = autobuz->get_Sens();

    autobuz->set_Viteza(
        strada->get_LimitaVitezaLaPozitie(pozitie)
    );

    // 2. Oprește dacă semaforul e roșu
    auto semafor = strada->get_SemaforLaCoord(pozitie);
    if (semafor && semafor->get_Culoare() == Culoare::Rosu)
        return;

    // 3. Oprește dacă e vehicul prioritar sau coloană
    if ((semafor && semafor->get_Culoare() == Culoare::Verde &&
         existaVehiculPrioritarAproape(pozitie, vehicule)) ||
        vehiculInFata(*autobuz, vehicule, deltaSecunde))
    {
        return;
    }

    // 4. Dacă e aproape de intersecție, alege direcția
    const int DIST_INTERSECTIE = 10;
    if (strada->existaIntersectieLaDistanta(pozitie, DIST_INTERSECTIE, sens)) {
        Sens directieNoua = alegeDirectieRandom(sens);
        if (directieNoua != opus(sens)) {
            autobuz->set_orientareViitoare(directieNoua);
        }
    }

    // 5. Dacă este exact în intersecție, schimbă direcția și strada
    int delta = autobuz->get_Viteza() / 10;
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
                autobuz->set_Pozitie(c);
                break;
            }
        }

        Sens viitor = autobuz->get_orientareViitoare();
        if (viitor != opus(sens)) {
            autobuz->schimbaSensul(viitor);
            auto stradaNoua = strada->get_StradaUrmatoare(intersectieGasita, viitor, strada);
            if (stradaNoua) {
                autobuz->schimbaStrada(stradaNoua);
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
        autobuz->schimbaSensul(opus(sens));
    }

    // 7. **Actualizează poziția cu deltaSecunde**
    autobuz->updatePosition(deltaSecunde, MAX_LENGTH, MAX_WIDTH);
}