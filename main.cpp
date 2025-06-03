#include <iostream>
#include <vector>
#include <string>
#include <memory>

#include "Coordinates.h"
#include "Street.h"
#include "Intersection.h"
#include "Stoplight.h"
#include "Utils.h"
#include "Vehicle.h"
#include "Simulator.h"
#include "GraphicSimulator.h"

int main() {
    try {
        const int MAX_LENGTH = 1000;
        const int MAX_WIDTH = 1000;
        const int syncDistance = 130;
        Simulator &sim = Simulator::getInstance();

        // Create streets
        std::vector<std::shared_ptr<Street>> streets;
        std::vector<std::shared_ptr<Intersection>> intersections;
        std::vector<std::shared_ptr<Stoplight>> stoplights;

        Coordinates coord1{100, 0};
        std::vector<std::pair<Coordinates<int>, int>> limits1 = {
            {Coordinates{100, 5}, 50},
            {Coordinates{100, 100}, 40},
            {Coordinates{100, 555}, 30}
        };

        auto street1 = std::make_shared<Street>("Main Street", coord1, Direction::Vertical, limits1);
        streets.push_back(street1);

        Coordinates coord2{0, 150};
        std::vector<std::pair<Coordinates<int>, int>> limits2 = {
            {Coordinates{25, 150}, 50},
            {Coordinates{260, 150}, 50},
            {Coordinates{700, 150}, 30}
        };

        auto street2 = std::make_shared<Street>("Small Street", coord2, Direction::Horizontal, limits2);
        streets.push_back(street2);

        Coordinates coord3{400, 0};
        std::vector<std::pair<Coordinates<int>, int>> limits3 = {
            {Coordinates{400, 150}, 50},
            {Coordinates{400, 550}, 50},
            {Coordinates{400, 850}, 30}
        };

        auto street3 = std::make_shared<Street>("Tiny Street", coord3, Direction::Vertical, limits3);
        streets.push_back(street3);

        Coordinates coord4{0, 550};
        std::vector<std::pair<Coordinates<int>, int>> limits4 = {
            {Coordinates{150, 550}, 50},
            {Coordinates{550, 550}, 50},
            {Coordinates{850, 550}, 30}
        };

        auto street4 = std::make_shared<Street>("Main Street", coord4, Direction::Horizontal, limits4);
        streets.push_back(street4);

        // Create intersections and stoplights
        for (size_t i = 0; i < streets.size(); ++i) {
            for (size_t j = i + 1; j < streets.size(); ++j) {
                auto s1 = streets[i];
                auto s2 = streets[j];

                if (intersects(s1, s2)) {
                    std::cout << "Intersection detected\n";
                    Coordinates interCoord = computeIntersection(s1, s2);

                    std::shared_ptr<Intersection> intersection;
                    if (s1->getDirection() == Direction::Vertical)
                        intersection = std::make_shared<Intersection>(interCoord, s1, s2);
                    else
                        intersection = std::make_shared<Intersection>(interCoord, s2, s1);

                    auto light1 = std::make_shared<Stoplight>(0, 0, 0, interCoord, s1);
                    auto light2 = std::make_shared<Stoplight>(0, 0, 0, interCoord, s2);

                    s1->addIntersection(interCoord, intersection);
                    s2->addIntersection(interCoord, intersection);
                    s1->addStoplight(interCoord, light1);
                    s2->addStoplight(interCoord, light2);

                    intersections.push_back(intersection);
                    stoplights.push_back(light1);
                    stoplights.push_back(light2);
                }
            }
        }

        // Synchronize stoplights
        initializeStoplights(streets, syncDistance);

        // Create vehicles
        auto car = std::make_shared<Car>(Coordinates{100, 0}, Orientation::Up, Orientation::Up, street1, 70);
        auto bus = std::make_shared<Bus>(Coordinates{100, 0}, Orientation::Up, Orientation::Up, street1, 70);
        auto priority = std::make_shared<PriorityVehicle>(Coordinates{100, 0}, Orientation::Up, Orientation::Up, street1, 70);
        auto bus2 = std::make_shared<Bus>(Coordinates{100, MAX_WIDTH}, Orientation::Down, Orientation::Down, street1, 70, 0);

        std::vector<std::shared_ptr<Vehicle>> vehicles = {car, bus, priority, bus2};

        // Add to simulator
        for (auto &v : vehicles)
            sim.addVehicle(v);
        for (auto &s : streets)
            sim.addStreet(s);
        for (auto &i : intersections)
            sim.addIntersection(i);
        for (auto &l : stoplights)
            sim.addStoplight(l);

        // Print simulator stats
        std::cout << "Total vehicles: " << sim.getVehicles().size() << '\n';
        std::cout << "Number of streets: " << sim.getStreets().size() << "\n";
        std::cout << "Number of vehicles: " << sim.getVehicles().size() << "\n";
        std::cout << "Number of stoplights: " << sim.getStoplights().size() << "\n";
        std::cout << "Number of intersections: " << sim.getIntersections().size() << "\n";

        GraphicSimulator graphics(sim, 1000, 1000);
        graphics.run();
    }
    catch (const VehicleMovementException &ex) {
        std::cerr << "Vehicle error: " << ex.what() << std::endl;
    }
    catch (const TrafficControlException &ex) {
        std::cerr << "Traffic control error: " << ex.what() << std::endl;
    }
    catch (const InvalidStartPositionException &ex) {
        std::cerr << "Start position error: " << ex.what() << std::endl;
    }
    catch (const TrafficSimulationException &ex) {
        std::cerr << "Simulation error: " << ex.what() << std::endl;
    }
    catch (const std::exception &ex) {
        std::cerr << "Standard exception: " << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
    }

    return 0;
}
