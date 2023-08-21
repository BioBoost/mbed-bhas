#pragma once

#include "event.h"

namespace BHAS::Events {

  // Event that contains a temperature

  class TemperatureEvent : public Event {

    public:
      TemperatureEvent(BHAS::Entities::Entity& entity, int8_t temperature)
        : Event(entity), _temperature(temperature) {

      }
    
    public:
      int8_t temperature() {
        return _temperature;
      }

    public:
      virtual std::string to_string() override {
        return "[TemperatureEvent] temperature = " + std::to_string(_temperature);
      }

    private:
      int8_t _temperature;

  };

};