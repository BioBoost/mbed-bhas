#pragma once

#include "mbed.h"
#include <stdint.h>
#include "event_context.h"
#include "entity.h"

namespace BHAS::Entities {

  class AliveTimer : public Entity {

    public:
      AliveTimer(uint8_t id, EventQueue& queue, EventQueue::duration updateTime = 300s, std::string description = "");

    public:
      // Register callback (in Node) to report time alive to
      void on_alive(Callback<void(BHAS::Events::EventContext*, uint32_t)> eventCallback);

    private:
      void notify_alive();

    public:
      virtual std::string to_string() const override;

    private:
      Callback<void(BHAS::Events::EventContext*, uint32_t)> _onAlive;

  };

};
