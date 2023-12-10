#pragma once
#include "../bhas_platform.h"

#if defined(PLATFORM_MBED)

#include "mbed.h"
#include <cstdint>
#include "entity.h"
#include "drivers/internal_temperature_sensor.h"

namespace BHAS::Entities {

  class InternalTemperature : public Entity {

    public:
      InternalTemperature(uint8_t id, EventQueue& queue, EventQueue::duration updateTime = 60s, std::string description = "");

    public:
      virtual std::string name() const override;

    private:
      void notify_temperature();

    private:
      BHAS::Drivers::InternalTemperature _internalTemperatureSensor;

  };

};

#endif
