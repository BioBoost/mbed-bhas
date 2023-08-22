#pragma once

#include "mbed.h"
#include <stdint.h>
#include "entity.h"
#include "action.h"

namespace BHAS::Entities {

  class Led : public Entity {

    private:
      enum class LedAction { TURN_ON, TURN_OFF, TOGGLE };
    
    public:
      Led(uint8_t id, PinName pin, std::string description = "");

    public:
      virtual std::string name() const override;

    public:
      virtual void process_action(Action& action) override;

    private:
      void on();
      void off();
      void toggle();

    private:
      DigitalOut _led;

  };

};
