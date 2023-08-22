#include "alive_timer.h"

namespace BHAS::Entities {

  AliveTimer::AliveTimer(uint8_t id, EventQueue& queue, EventQueue::duration updateTime, std::string description)
    : Entity(id, description) {

    queue.call_every(updateTime, callback(this, &AliveTimer::notify_alive));
  }

  void AliveTimer::notify_alive() {
    time_t now = time(NULL);

    Event event(*this, Event::Type::ALIVE, {
      static_cast<uint8_t>((now >> 24) & 0xFF),
      static_cast<uint8_t>((now >> 16) & 0xFF),
      static_cast<uint8_t>((now >> 8) & 0xFF),
      static_cast<uint8_t>((now >> 0) & 0xFF),
    });
    
    call_event_handler(event);
  }

  std::string AliveTimer::name() const {
    return "AliveTimer";
  }

};
