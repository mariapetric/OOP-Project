#ifndef SIMULATOR_GRAPHICS_H
#define SIMULATOR_GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "Simulator.h"
#include <map>

class GraphicSimulator {
private:
    Simulator &sim;
    sf::RenderWindow window;
    int width, height;

    sf::Texture carTexture, busTexture, priorityTexture;

    void drawVehicles();
    void drawStreets();
    void drawStoplights();

public:
    GraphicSimulator(Simulator &simulator, int width, int height);

    void run(); // main graphics loop
};

#endif // SIMULATOR_GRAPHICS_H
