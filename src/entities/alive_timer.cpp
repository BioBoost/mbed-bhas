#include "alive_timer.h"
#include "mbed_trace.h"

#define TRACE_GROUP "BHAS MessageLogger"

namespace BHAS::Entities {

  AliveTimer::AliveTimer(uint8_t id, EventQueue& queue, EventQueue::duration updateTime, std::string description)
    : Entity(id, description) {

    _timer.start();
    queue.call_every(updateTime, callback(this, &AliveTimer::notify_alive));
  }

  void AliveTimer::notify_alive() {
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(_timer.elapsed_time()).count();

    Event event(*this, Event::Type::ALIVE, {
      static_cast<uint8_t>(seconds >> 24),
      static_cast<uint8_t>(seconds >> 16),
      static_cast<uint8_t>(seconds >> 8),
      static_cast<uint8_t>(seconds >> 0),
    });
    
    call_event_handler(event);
  }

  std::string AliveTimer::name() const {
    return "AliveTimer";
  }

};
