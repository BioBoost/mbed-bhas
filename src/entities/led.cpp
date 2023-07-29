#include "led.h"

namespace BHAS::Entities {

  Led::Led(uint8_t id, PinName pin, std::string description)
    : Entity(id, description), _led(pin) {
  }

  void Led::on() {
    _led = true;
  }

  void Led::off() {
    _led = false;
  }

  void Led::toggle() {
    _led = !_led;
  }

  std::string Led::to_string() const {
    return Entity::to_string() + " - type: Led";
  }

};
