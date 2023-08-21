#pragma once

#include "event.h"

namespace BHAS::Events {

  // Event that contains the time this device is alive

  class AliveTimeEvent : public Event {

    public:
      AliveTimeEvent(BHAS::Entities::Entity& entity, uint32_t seconds)
        : Event(entity), _seconds(seconds) {

      }
    
    public:
      uint32_t seconds() {
        return _seconds;
      }

    public:
      virtual std::string to_string() override {
        return "[AliveTimeEvent] seconds = " + std::to_string(static_cast<unsigned long>(_seconds));
      }

    private:
      uint32_t _seconds;

  };

};