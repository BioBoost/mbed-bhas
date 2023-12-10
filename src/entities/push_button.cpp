#include "push_button.h"

#if defined(PLATFORM_MBED)

namespace BHAS::Entities {

  PushButton::PushButton(uint8_t id, EventQueue& queue, PinName pin, std::string description)
    : Entity(id, description), _queue(queue), _button(pin) {

    _button.fall(callback(this, &PushButton::falling_edge));
    _button.rise(callback(this, &PushButton::rising_edge));
  }

  void PushButton::falling_edge() {
    // This is ISR !
    _timer.start();

    // TODO: DOWN event
  }

  void PushButton::rising_edge() {
    // This is ISR !
    _timer.stop();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(_timer.elapsed_time()).count();
    _timer.reset();

    // TODO: UP event

    ButtonEvent type = (milliseconds <= MBED_CONF_BHAS_PUSH_BUTTON_SHORT_PRESS_THRESHOLD_MS ? ButtonEvent::SHORT_PRESS : ButtonEvent::LONG_PRESS);
    _queue.call(callback(this, &PushButton::notify_event), type);   // Currently in ISR context ! Need to move to event queue
  }

  void PushButton::notify_event(ButtonEvent type) {
    Event event(*this, Event::Type::BUTTON, { static_cast<uint8_t>(type) });
    call_event_handler(event);
  }

  std::string PushButton::name() const {
    return "PushButton";
  }

};

#endif
