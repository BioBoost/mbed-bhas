#pragma once

#include "mbed.h"
#include <stdint.h>
#include "alive_time_event.h"
#include "entity.h"

namespace BHAS::Entities {

  class AliveTimer : public Entity {

    public:
      AliveTimer(uint8_t id, EventQueue& queue, EventQueue::duration updateTime = 300s, std::string description = "");

    public:
      void on_alive(Callback<void(BHAS::Events::AliveTimeEvent&)> eventCallback);

    private:
      void notify_alive();

    public:
      virtual std::string to_string() const override;

    private:
      Callback<void(BHAS::Events::AliveTimeEvent&)> _onAlive;

  };

};
