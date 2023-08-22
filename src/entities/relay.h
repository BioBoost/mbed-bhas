#pragma once

#include "mbed.h"
#include <stdint.h>
#include "entity.h"
#include "action.h"

namespace BHAS::Entities {

  class Relay : public Entity {

    public:
      Relay(uint8_t id, PinName pin, std::string description = "");

    public:
      void on();
      void off();
      void toggle();

    public:
      virtual std::string name() const override;

    public:
      virtual void process_action(Actions::Action& action) override {};

    private:
      DigitalOut _relay;

  };

};
