#include <TrafficSimulationException.h>

TrafficSimulationException::TrafficSimulationException(const std::string message_) :
    message{message_} {}

const char* TrafficSimulationException::what() const noexcept {
    return message.c_str();
}

VehicleMovementException::VehicleMovementException(const std::string message_)
      : TrafficSimulationException("Eroare la mișcarea vehiculului: " +  message_) {}

TrafficControlException::TrafficControlException(const std::string message_)
        : TrafficSimulationException("Eroare la controlul traficului: " + message_) {}

InvalidStartPositionException::InvalidStartPositionException(const std::string message_)
        : TrafficSimulationException("Poziția de început este invalidă: " + message_) {}