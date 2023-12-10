#pragma once
#include "../bhas_platform.h"

#if defined(PLATFORM_MBED)

#include <cstdint>
#include "digital_output.h"

namespace BHAS::Entities {

  class IndicatorLed : public DigitalOutput {

    public:
      IndicatorLed(uint8_t id, PinName pin, std::string description = "");

    public:
      virtual std::string name() const override;

  };

};

#endif
