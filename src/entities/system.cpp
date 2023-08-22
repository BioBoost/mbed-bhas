#include "system.h"

namespace BHAS::Entities {

  System::System(uint8_t id, EventQueue& queue, std::string description)
    : Entity(id, description) {

    queue.call(callback(this, &System::notify_boot));
  }

  void System::notify_boot() {
    Event event(*this, Event::Type::BOOT, { });
    call_event_handler(event);
  }

  std::string System::name() const {
    return "System";
  }

};
