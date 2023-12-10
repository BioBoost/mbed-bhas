#pragma once
#include "../bhas_platform.h"

#if defined(PLATFORM_MBED)

#include "mbed.h"
#include <cstdint>
#include "entity.h"
#include "action.h"

namespace BHAS::Entities {

  class DigitalOutput : public Entity {

    private:
      enum class OutputAction { TURN_ON, TURN_OFF, TOGGLE };
    
    public:
      DigitalOutput(uint8_t id, PinName pin, std::string description = "");

    public:
      virtual std::string name() const override;

    public:
      virtual void process_action(Action& action) override;

    private:
      void on();
      void off();
      void toggle();

    private:
      DigitalOut _out;

  };

};

#endif