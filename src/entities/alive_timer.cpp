#include "alive_timer.h"

namespace BHAS::Entities {

  AliveTimer::AliveTimer(uint8_t id, EventQueue& queue, EventQueue::duration updateTime, std::string description)
    : Entity(id, description) {

    queue.call_every(updateTime, callback(this, &AliveTimer::notify_alive));
  }

  void AliveTimer::on_alive(Callback<void(BHAS::Events::AliveTimeEvent&)> eventCallback) {
    _onAlive = eventCallback;
  }

  void AliveTimer::notify_alive() {
    if (_onAlive) {
      BHAS::Events::AliveTimeEvent event(*this, time(NULL));
      _onAlive.call(event);
    }
  }

  std::string AliveTimer::to_string() const {
    return Entity::to_string() + " - type: AliveTimer";
  }

};
