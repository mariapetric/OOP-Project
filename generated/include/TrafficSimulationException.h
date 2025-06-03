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

class VehicleMovementException : public TrafficSimulationException {
public:
  explicit VehicleMovementException(const std::string msg);
};

class TrafficControlException : public TrafficSimulationException {
public:
    explicit TrafficControlException(const std::string msg);
};

class InvalidStartPositionException : public TrafficSimulationException {
public:
    explicit InvalidStartPositionException(const std::string msg);
};


#endif //TRAFFICSIMULATIONEXCEPTION_H
