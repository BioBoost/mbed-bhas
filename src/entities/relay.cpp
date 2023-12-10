#include "relay.h"

#if defined(PLATFORM_MBED)

namespace BHAS::Entities {

  Relay::Relay(uint8_t id, PinName pin, std::string description)
    : DigitalOutput(id, pin, description) {
  }

  std::string Relay::name() const {
    return "Relay";
  }

};

#endif
