#include "relay.h"

namespace BHAS::Entities {

  Relay::Relay(uint8_t id, PinName pin, std::string description)
    : Entity(id, description), _relay(pin) {
  }

  void Relay::on() {
    _relay = true;
  }

  void Relay::off() {
    _relay = false;
  }

  void Relay::toggle() {
    _relay = !_relay;
  }

  std::string Relay::to_string() const {
    return Entity::to_string() + " - type: Relay";
  }

};
