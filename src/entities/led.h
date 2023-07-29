#pragma once

#include "mbed.h"
#include <stdint.h>
#include "entity.h"

namespace BHAS::Entities {

  class Led : public Entity {

    public:
      Led(uint8_t id, PinName pin, std::string description = "");

    public:
      void on();
      void off();
      void toggle();

    public:
      virtual std::string to_string() const override;

    private:
      DigitalOut _led;

  };

};
