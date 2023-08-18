#pragma once

#include "mbed.h"
#include <stdint.h>
#include "event_context.h"
#include "entity.h"
#include "drivers/internal_temperature_sensor.h"

namespace BHAS::Entities {

  class InternalTemperature : public Entity {

    public:
      InternalTemperature(uint8_t id, EventQueue& queue, EventQueue::duration updateTime = 60s, std::string description = "");

    public:
      // Register callback (in Node) to report temperature to
      void on_temperature(Callback<void(BHAS::Events::EventContext*,int8_t)> eventCallback);

    private:
      void notify_temperature();

    public:
      virtual std::string to_string() const override;

    private:
      BHAS::Drivers::InternalTemperature _internalTemperatureSensor;
      Callback<void(BHAS::Events::EventContext*,int8_t)> _onTemperature;

  };

};
