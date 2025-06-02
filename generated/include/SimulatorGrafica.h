#ifndef SIMULATOR_GRAFICA_H
#define SIMULATOR_GRAFICA_H

#include <SFML/Graphics.hpp>
#include "Simulator.h"
#include <map>

class SimulatorGrafica {
private:
    Simulator& sim;
    sf::RenderWindow fereastra;
    int latime, inaltime;

    sf::Texture masinaTexture, autobuzTexture, prioritarTexture;

    void deseneazaVehicule();
    void deseneazaStrazi();
    void deseneazaSemafore();

public:
    SimulatorGrafica(Simulator& simulator, int width, int height);
    void ruleaza();  // loop-ul grafic
};


#endif //SIMULATORGRAFICA_H
