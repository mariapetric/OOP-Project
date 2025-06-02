// SimulatorGrafica.cpp
#include "SimulatorGrafica.h"

SimulatorGrafica::SimulatorGrafica(Simulator& simulator, int width, int height)
        : sim(simulator),
          fereastra(sf::VideoMode(width, height), "Simulare Trafic"),
          latime(width), inaltime(height)
{
    // Încarcă texturile
    masinaTexture.loadFromFile("res/masina1.png");
    autobuzTexture.loadFromFile("res/autobuz1.png");
    prioritarTexture.loadFromFile("res/prioritar1.png");
}

// Desenează străzile ca dreptunghiuri gri închis, cu linie punctată albă pe mijloc
void SimulatorGrafica::deseneazaStrazi() {
    // grosimea străzii: 6% din lățimea ferestrei (0.06f * width)
    float streetThickness = latime * 0.06f;

    for (auto& strada : sim.getStrazi()) {
        auto start = strada->get_CoordonataStart();
        auto end   = strada->get_CoordonataFinal();
        Orientare orient = strada->get_OrientareStrada();

        // Culoarea străzii: gri închis
        sf::Color streetColor(50, 50, 50);

        if (orient == Orientare::Orizontala) {
            // lungimea și poziția orizontală
            float x1 = static_cast<float>(start.get_x());
            float y  = static_cast<float>(start.get_y());
            float x2 = static_cast<float>(end.get_x());
            if (x2 < x1) std::swap(x1, x2);

            // Dreptunghiul străzii
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(x2 - x1, streetThickness));
            rect.setFillColor(streetColor);
            // poziționează astfel încât centrul străzii să fie la y
            rect.setPosition(x1, y - streetThickness / 2.0f);
            fereastra.draw(rect);

            // Desenează linia punctată albă pe mijloc
            float dashLength = 20.0f;
            float gapLength  = 20.0f;
            float cx = x1;
            float centerY = y - 1.0f; // 1px sub centrul vertical al străzii pentru contrast
            while (cx + dashLength < x2) {
                sf::RectangleShape dash(sf::Vector2f(dashLength, 2.0f));
                dash.setFillColor(sf::Color::White);
                dash.setPosition(cx, centerY);
                fereastra.draw(dash);
                cx += dashLength + gapLength;
            }
        }
        else { // Orientare::Verticala
            float x  = static_cast<float>(start.get_x());
            float y1 = static_cast<float>(start.get_y());
            float y2 = static_cast<float>(end.get_y());
            if (y2 < y1) std::swap(y1, y2);

            // Dreptunghiul străzii
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(streetThickness, y2 - y1));
            rect.setFillColor(streetColor);
            rect.setPosition(x - streetThickness / 2.0f, y1);
            fereastra.draw(rect);

            // Desenează linia punctată albă pe mijloc
            float dashLength = 20.0f;
            float gapLength  = 20.0f;
            float cy = y1;
            float centerX = x - 1.0f; // 1px stânga de centrul orizontal al străzii
            while (cy + dashLength < y2) {
                sf::RectangleShape dash(sf::Vector2f(2.0f, dashLength));
                dash.setFillColor(sf::Color::White);
                dash.setPosition(centerX, cy);
                fereastra.draw(dash);
                cy += dashLength + gapLength;
            }
        }
    }
}

// Desenează vehiculele offsetate pe banda corespunzătoare direcției
void SimulatorGrafica::deseneazaVehicule() {
    // Grosimea străzii (6% din lățimea ferestrei)
    float streetThickness = latime * 0.06f;

    for (auto& v : sim.getVehicule()) {
        if (!v) continue;

        sf::Sprite sprite;
        if (std::dynamic_pointer_cast<Autobuz>(v))
            sprite.setTexture(autobuzTexture);
        else if (std::dynamic_pointer_cast<VehiculPrioritar>(v))
            sprite.setTexture(prioritarTexture);
        else
            sprite.setTexture(masinaTexture);

        auto poz = v->get_PozitieVehicul();
        auto sens = v->get_Sens();
        auto strada = v->get_Strada();

        float dxOffset = 0.0f;
        float dyOffset = 0.0f;

        // Dacă strada e VERTICALĂ, vehiculele se deplasează în sus/jos,
        // așa că îi mutăm pe orizontală (±streetThickness/4)
        if (strada->get_OrientareStrada() == Orientare::Verticala) {
            if (sens == Sens::Sus) {
                dxOffset = -streetThickness / 4.0f;
            }
            else if (sens == Sens::Jos) {
                dxOffset =  streetThickness / 4.0f;
            }
        }
        // Dacă strada e ORIZONTALĂ, vehiculele se deplasează stânga/dreapta,
        // așa că îi mutăm pe verticală (±streetThickness/4)
        else { // Orientare::Orizontala
            if (sens == Sens::Dreapta) {
                dyOffset =  streetThickness / 4.0f;
            }
            else if (sens == Sens::Stanga) {
                dyOffset = -streetThickness / 4.0f;
            }
        }

        sprite.setPosition(
            static_cast<float>(poz.get_x()) + dxOffset,
            static_cast<float>(poz.get_y()) + dyOffset
        );
        sprite.setScale(0.04f, 0.04f);
        fereastra.draw(sprite);
    }
}


void SimulatorGrafica::deseneazaSemafore() {
    // 1) Grosimea străzii (6% din lățimea ferestrei)
    float streetThickness = latime * 0.06f;
    // 2) Raza cercului (≈15% din grosimea străzii)
    float radius = streetThickness * 0.15f;

    // 3) Creăm un map gol care va grupa semafoarele după coordonata intersecției
    std::map<Coordonate<int>, std::vector<std::shared_ptr<Semafor>>> mapInter;

    // 4) Populăm mapInter cu fiecare semafor, grupându-l după get_Coordonate()
    for (auto& semafor : sim.getSemafoare()) {
        Coordonate<int> coordInter = semafor->get_Coordonate();
        mapInter[coordInter].push_back(semafor);
    }

    // 5) Acum, pentru fiecare intrare din mapInter (adică fiecare intersecție):
    for (auto& [coordInter, vecSemafoare] : mapInter) {
        float cx = static_cast<float>(coordInter.get_x());
        float cy = static_cast<float>(coordInter.get_y());

        // 5.1) Identificăm semaforul atașat direcției verticale și cel atașat direcției orizontale
        std::shared_ptr<Semafor> semVertical  = nullptr;
        std::shared_ptr<Semafor> semOrizontal = nullptr;

        for (auto& s : vecSemafoare) {
            if (!s->getStrada()) continue;
            Orientare o = s->getStrada()->get_OrientareStrada();
            if (o == Orientare::Verticala)    semVertical  = s;
            else if (o == Orientare::Orizontala) semOrizontal = s;
        }

        // 5.2) Dacă nu există nici vertical și nici orizontal, continuăm
        if (!semVertical && !semOrizontal)
            continue;

        // 5.3) Determinăm culoarea verticală (din semVertical) și culoarea opusă pentru orizontal
        sf::Color cVertical  = sf::Color::Black;
        sf::Color cOrizontal = sf::Color::Black;

        if (semVertical) {
            switch (semVertical->get_Culoare()) {
                case Culoare::Verde:  cVertical = sf::Color(0, 200, 0);   break;
                case Culoare::Galben: cVertical = sf::Color(255, 200, 0); break;
                case Culoare::Rosu:   cVertical = sf::Color(200, 0, 0);   break;
                default:              cVertical = sf::Color::Black;      break;
            }
            // adultează culoarea opusă:
            if      (semVertical->get_Culoare() == Culoare::Verde)  cOrizontal = sf::Color(200, 0, 0);
            else if (semVertical->get_Culoare() == Culoare::Rosu)   cOrizontal = sf::Color(0, 200, 0);
            else /*Galben*/                                        cOrizontal = cVertical;
        }
        else {
            // Dacă lipsește vertical, ne bazăm doar pe semOrizontal pentru a decide
            switch (semOrizontal->get_Culoare()) {
                case Culoare::Verde:  cOrizontal = sf::Color(0, 200, 0);   break;
                case Culoare::Galben: cOrizontal = sf::Color(255, 200, 0); break;
                case Culoare::Rosu:   cOrizontal = sf::Color(200, 0, 0);   break;
                default:              cOrizontal = sf::Color::Black;      break;
            }
            if      (semOrizontal->get_Culoare() == Culoare::Verde)  cVertical = sf::Color(200, 0, 0);
            else if (semOrizontal->get_Culoare() == Culoare::Rosu)   cVertical = sf::Color(0, 200, 0);
            else /*Galben*/                                         cVertical = cOrizontal;
        }

        // 5.4) Desenăm semafoarele verticale (sus/jos), dacă există semVertical
        if (semVertical) {
            sf::CircleShape cercSus(radius);
            cercSus.setFillColor(cVertical);
            cercSus.setOrigin(radius, radius);
            cercSus.setPosition(cx, cy - streetThickness/2.0f - radius);
            fereastra.draw(cercSus);

            sf::CircleShape cercJos(radius);
            cercJos.setFillColor(cVertical);
            cercJos.setOrigin(radius, radius);
            cercJos.setPosition(cx, cy + streetThickness/2.0f + radius);
            fereastra.draw(cercJos);
        }

        // 5.5) Desenăm semafoarele orizontale (stânga/dreapta), dacă există semOrizontal
        if (semOrizontal) {
            sf::CircleShape cercStanga(radius);
            cercStanga.setFillColor(cOrizontal);
            cercStanga.setOrigin(radius, radius);
            cercStanga.setPosition(cx - streetThickness/2.0f - radius, cy);
            fereastra.draw(cercStanga);

            sf::CircleShape cercDreapta(radius);
            cercDreapta.setFillColor(cOrizontal);
            cercDreapta.setOrigin(radius, radius);
            cercDreapta.setPosition(cx + streetThickness/2.0f + radius, cy);
            fereastra.draw(cercDreapta);
        }
    }
}



void SimulatorGrafica::ruleaza() {
    sf::Clock ceasGlobal;
    sf::Time ultimaActualizare = sf::Time::Zero;

    while (fereastra.isOpen()) {
        // 1) Event-uri SFML
        sf::Event event;
        while (fereastra.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fereastra.close();
        }

        // 2) Calcul deltaTime
        sf::Time acum = ceasGlobal.getElapsedTime();
        float deltaSec = (acum - ultimaActualizare).asSeconds();
        if (deltaSec > 0.0f) {
            // 3) Actualizează simularea cu deltaSec
            sim.simuleazaTimp(deltaSec);
            ultimaActualizare = acum;
        }

        // 4) Desenare fundal verde-blând
        fereastra.clear(sf::Color(80, 130, 80)); // un verde nu foarte aprins

        // 5) Desenează străzi, semafoare, vehicule
        deseneazaStrazi();
        deseneazaSemafore();
        deseneazaVehicule();

        // 6) Afișează frame-ul
        fereastra.display();
    }
}
