#include "internal_temperature.h"

#if defined(PLATFORM_MBED)

namespace BHAS::Entities {

  InternalTemperature::InternalTemperature(uint8_t id, EventQueue& queue, EventQueue::duration updateTime, std::string description)
    : Entity(id, description) {

    queue.call_every(updateTime, callback(this, &InternalTemperature::notify_temperature));
  }

  void InternalTemperature::notify_temperature() {
    Event event(*this, Event::Type::TEMPERATURE, { _internalTemperatureSensor.temperature() });
    call_event_handler(event);
  }

  std::string InternalTemperature::name() const {
    return "InternalTemperature";
  }

};

#endif
