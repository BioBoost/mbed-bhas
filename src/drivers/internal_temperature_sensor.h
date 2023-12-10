#pragma once
#include "../bhas_platform.h"

#if defined(PLATFORM_MBED)
#include "mbed.h"
#include <cstdint>

namespace BHAS::Drivers {

  class InternalTemperature {

    public:
      InternalTemperature();

    public:
      int8_t temperature();

    private:
#if !defined(TARGET_LPC1768)
      AnalogIn _internalTemperature;
      AnalogIn _vrefInt;
#endif

  };

};
#endif