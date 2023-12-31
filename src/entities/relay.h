#pragma once

#include <stdint.h>
#include "digital_output.h"

namespace BHAS::Entities {

  class Relay : public DigitalOutput {

    public:
      Relay(uint8_t id, PinName pin, std::string description = "");

    public:
      virtual std::string name() const override;

  };

};
