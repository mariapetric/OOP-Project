#include "GraphicSimulator.h"

GraphicSimulator::GraphicSimulator(Simulator &simulator, int width, int height)
    : sim(simulator),
      window(sf::VideoMode(width, height), "Traffic Simulation"),
      width(width), height(height) {
    carTexture.loadFromFile("res/masina1.png");
    busTexture.loadFromFile("res/autobuz1.png");
    priorityTexture.loadFromFile("res/prioritar1.png");
}

void GraphicSimulator::drawStreets() {
    float streetThickness = width * 0.06f;

    for (auto &street: sim.getStreets()) {
        auto start = street->getStartCoordinate();
        auto end = street->getEndCoordinate();
        Direction orient = street->getDirection();

        sf::Color streetColor(50, 50, 50);

        if (orient == Direction::Horizontal) {
            float x1 = static_cast<float>(start.get_x());
            float y = static_cast<float>(start.get_y());
            float x2 = static_cast<float>(end.get_x());
            if (x2 < x1) std::swap(x1, x2);

            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(x2 - x1, streetThickness));
            rect.setFillColor(streetColor);
            rect.setPosition(x1, y - streetThickness / 2.0f);
            window.draw(rect);

            float dashLength = 20.0f, gapLength = 20.0f, cx = x1, centerY = y - 1.0f;
            while (cx + dashLength < x2) {
                sf::RectangleShape dash(sf::Vector2f(dashLength, 2.0f));
                dash.setFillColor(sf::Color::White);
                dash.setPosition(cx, centerY);
                window.draw(dash);
                cx += dashLength + gapLength;
            }
        } else {
            float x = static_cast<float>(start.get_x());
            float y1 = static_cast<float>(start.get_y());
            float y2 = static_cast<float>(end.get_y());
            if (y2 < y1) std::swap(y1, y2);

            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(streetThickness, y2 - y1));
            rect.setFillColor(streetColor);
            rect.setPosition(x - streetThickness / 2.0f, y1);
            window.draw(rect);

            float dashLength = 20.0f, gapLength = 20.0f, cy = y1, centerX = x - 1.0f;
            while (cy + dashLength < y2) {
                sf::RectangleShape dash(sf::Vector2f(2.0f, dashLength));
                dash.setFillColor(sf::Color::White);
                dash.setPosition(centerX, cy);
                window.draw(dash);
                cy += dashLength + gapLength;
            }
        }
    }
}

void GraphicSimulator::drawVehicles() {
    float streetThickness = width * 0.06f;

    for (auto &v: sim.getVehicles()) {
        if (!v) continue;

        sf::Sprite sprite;
        if (std::dynamic_pointer_cast<Bus>(v)) sprite.setTexture(busTexture);
        else if (std::dynamic_pointer_cast<PriorityVehicle>(v)) sprite.setTexture(priorityTexture);
        else sprite.setTexture(carTexture);

        auto pos = v->get_Position();
        auto orientation = v->get_Orientation();
        auto street = v->get_Street();

        float dx = 0.0f, dy = 0.0f;

        if (street->getDirection() == Direction::Vertical) {
            dx = (orientation == Orientation::Up ? -1 : 1) * streetThickness / 4.0f;
        } else {
            dy = (orientation == Orientation::Right ? 1 : -1) * streetThickness / 4.0f;
        }

        sprite.setPosition(static_cast<float>(pos.get_x()) + dx,
                           static_cast<float>(pos.get_y()) + dy);
        sprite.setScale(0.04f, 0.04f);
        window.draw(sprite);
    }
}

void GraphicSimulator::drawStoplights() {
    float thickness = width * 0.06f;
    float radius = thickness * 0.15f;

    std::map<Coordinates<int>, std::vector<std::shared_ptr<Stoplight>>> interMap;
    for (auto &s: sim.getStoplights()) {
        interMap[s->getCoordinates()].push_back(s);
    }

    for (auto &[coord, lights]: interMap) {
        float cx = static_cast<float>(coord.get_x());
        float cy = static_cast<float>(coord.get_y());

        std::shared_ptr<Stoplight> vertical = nullptr, horizontal = nullptr;

        for (auto &s: lights) {
            if (!s->getStreet()) continue;
            auto o = s->getStreet()->getDirection();
            if (o == Direction::Vertical) vertical = s;
            else horizontal = s;
        }

        if (!vertical && !horizontal) continue;

        sf::Color cV = sf::Color::Black, cH = sf::Color::Black;

        if (vertical) {
            switch (vertical->getColor()) {
                case Color::Green: cV = sf::Color(0, 200, 0); cH = sf::Color(200, 0, 0); break;
                case Color::Yellow: cV = sf::Color(255, 200, 0); cH = sf::Color(255, 200, 0); break;
                case Color::Red: cV = sf::Color(200, 0, 0); cH = sf::Color(0, 200, 0); break;
                default: break;
            }
        } else if (horizontal) {
            switch (horizontal->getColor()) {
                case Color::Green: cH = sf::Color(0, 200, 0); cV = sf::Color(200, 0, 0); break;
                case Color::Yellow: cH = sf::Color(255, 200, 0); cV = sf::Color(255, 200, 0); break;
                case Color::Red: cH = sf::Color(200, 0, 0); cV = sf::Color(0, 200, 0); break;
                default: break;
            }
        }

        if (vertical) {
            sf::CircleShape top(radius);
            top.setFillColor(cV);
            top.setOrigin(radius, radius);
            top.setPosition(cx, cy - thickness / 2.0f - radius);
            window.draw(top);

            sf::CircleShape bottom(radius);
            bottom.setFillColor(cV);
            bottom.setOrigin(radius, radius);
            bottom.setPosition(cx, cy + thickness / 2.0f + radius);
            window.draw(bottom);
        }

        if (horizontal) {
            sf::CircleShape left(radius);
            left.setFillColor(cH);
            left.setOrigin(radius, radius);
            left.setPosition(cx - thickness / 2.0f - radius, cy);
            window.draw(left);

            sf::CircleShape right(radius);
            right.setFillColor(cH);
            right.setOrigin(radius, radius);
            right.setPosition(cx + thickness / 2.0f + radius, cy);
            window.draw(right);
        }
    }
}

void GraphicSimulator::run() {
    sf::Clock clock;
    sf::Time lastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time now = clock.getElapsedTime();
        float delta = (now - lastUpdate).asSeconds();

        if (delta > 0.0f) {
            sim.simulateTime(delta);
            lastUpdate = now;
        }

        window.clear(sf::Color(80, 130, 80));
        drawStreets();
        drawStoplights();
        drawVehicles();
        window.display();
    }
}
