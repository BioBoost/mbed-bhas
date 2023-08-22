#pragma once

#include "mbed.h"
#include <stdint.h>
#include "temperature_event.h"
#include "entity.h"
#include "drivers/internal_temperature_sensor.h"

namespace BHAS::Entities {

  class InternalTemperature : public Entity {

    public:
      InternalTemperature(uint8_t id, EventQueue& queue, EventQueue::duration updateTime = 60s, std::string description = "");

    public:
      void on_temperature(Callback<void(BHAS::Events::TemperatureEvent&)> eventCallback);

    private:
      void notify_temperature();

    public:
      virtual std::string name() const override;

    public:
      virtual void process_action(Actions::Action& action) override {};

    private:
      BHAS::Drivers::InternalTemperature _internalTemperatureSensor;
      Callback<void(BHAS::Events::TemperatureEvent&)> _onTemperature;

  };

};
