#include "push_button.h"

namespace BHAS::Entities {

  PushButton::PushButton(uint8_t id, EventQueue& queue, PinName pin, std::string description)
    : Entity(id, description), _queue(queue), _button(pin) {

    _button.fall(callback(this, &PushButton::falling_edge));
    _button.rise(callback(this, &PushButton::rising_edge));
  }

  void PushButton::on_event(Callback<void(BHAS::Events::ButtonEvent&)> eventCallback) {
    _onEvent = eventCallback;
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

    Events::ButtonEvent::Type type = (milliseconds <= MBED_CONF_BHAS_PUSH_BUTTON_SHORT_PRESS_THRESHOLD_MS ? Events::ButtonEvent::Type::SHORT_PRESS : Events::ButtonEvent::Type::LONG_PRESS);
    _queue.call(callback(this, &PushButton::notify_press), type);   // Currently in ISR context ! Need to move to event queue

    // TODO: UP event
  }

  void PushButton::notify_press(Events::ButtonEvent::Type type) {
    if (_onEvent) {
      BHAS::Events::ButtonEvent event(*this, type);
      _onEvent.call(event);
    }
  }

  std::string PushButton::to_string() const {
    return Entity::to_string() + " - type: PushButton";
  }

};
