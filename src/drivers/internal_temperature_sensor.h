#pragma once

#include "mbed.h"
#include <stdint.h>

namespace BHAS::Drivers {

  class InternalTemperature {

    public:
      InternalTemperature();

    public:
      int8_t temperature();

    private:
      AnalogIn _internalTemperature;
      AnalogIn _vrefInt;

  };

};
