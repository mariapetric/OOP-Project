#ifndef TRAFFICSIMULATIONEXCEPTION_H
#define TRAFFICSIMULATIONEXCEPTION_H
#include <iostream>
#include <exception>
#include <string>
#include <memory>

class TrafficSimulationException : public std::exception {
private:
  std::string message;

public:
  explicit TrafficSimulationException(std::string message);
  const char* what() const noexcept override;
};

// pt erori la miscarea vehiculelor - intrec limita de viteza, se afla intr-o pozitie invalida
class VehicleMovementException : public TrafficSimulationException {
public:
  explicit VehicleMovementException(const std::string msg);
};

// erori legate de semafoare sau intersectii - semafoarele nu functioneaza corect
class TrafficControlException : public TrafficSimulationException {
public:
    explicit TrafficControlException(const std::string msg);
};

// cand un vehicul nu e plasat la inceput unei strazi sau o strada nu e plasata pe margine
class InvalidStartPositionException : public TrafficSimulationException {
public:
    explicit InvalidStartPositionException(const std::string msg);
};


#endif //TRAFFICSIMULATIONEXCEPTION_H
