#pragma once

#include "mbed.h"
#include <stdint.h>
#include "entity.h"

namespace BHAS::Entities {

  class Led : public Entity {

    public:
      Led(uint8_t id, PinName pin);

    public:
      void on();
      void off();
      void toggle();

    private:
      DigitalOut _led;

  };

};
