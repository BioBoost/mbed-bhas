#include "indicator_led.h"

#if defined(PLATFORM_MBED)

namespace BHAS::Entities {

  IndicatorLed::IndicatorLed(uint8_t id, PinName pin, std::string description)
    : DigitalOutput(id, pin, description) {
  }

  std::string IndicatorLed::name() const {
    return "IndicatorLed";
  }

};

#endif
