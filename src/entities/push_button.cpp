#include "push_button.h"
#include "mbed.h"
#include "entity_event.h"
#include "entity_event_handler.h"

namespace BHAS {

  PushButton::PushButton(uint8_t id, PinName pin, EntityEventHandler * eventHandler)
    : Entity(id), button(pin, PinMode::PullUp), _eventHandler(eventHandler) {
    
    button.fall(callback(this, &PushButton::handle_fall_event));
    button.rise(callback(this, &PushButton::handle_rise_event));
  }

  void PushButton::handle_fall_event() {
    timer.start();
  }

  void PushButton::handle_rise_event() {
    timer.stop();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(timer.elapsed_time()).count();
    timer.reset();

    // TODO: Determine type of event and such ...
    EntityEvent event(this, EntityEvent::EventType::SHORT_PRESS);
    _eventHandler->handle_event(event);
  }

};