#include "internal_temperature.h"

namespace BHAS::Entities {

  InternalTemperature::InternalTemperature(uint8_t id, EventQueue& queue, EventQueue::duration updateTime, std::string description)
    : Entity(id, description) {

    queue.call_every(updateTime, callback(this, &InternalTemperature::notify_temperature));
  }

  void InternalTemperature::on_temperature(Callback<void(BHAS::Events::EventContext*,int8_t)> eventCallback) {
    _onTemperature = eventCallback;
  }

  void InternalTemperature::notify_temperature() {
    if (_onTemperature) {
      BHAS::Events::EventContext context(*this);
      _onTemperature.call(&context, _internalTemperatureSensor.temperature());
    }
  }

  std::string InternalTemperature::to_string() const {
    return Entity::to_string() + " - type: InternalTemperature";
  }

};
