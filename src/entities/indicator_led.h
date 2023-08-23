#pragma once

#include <stdint.h>
#include "digital_output.h"

namespace BHAS::Entities {

  class IndicatorLed : public DigitalOutput {

    public:
      IndicatorLed(uint8_t id, PinName pin, std::string description = "");

    public:
      virtual std::string name() const override;

  };

};
