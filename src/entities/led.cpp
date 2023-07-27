#include "led.h"

namespace BHAS::Entities {

  Led::Led(uint8_t id, PinName pin)
    : Entity(id), _led(pin) {
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

};
