#include "push_button.h"

namespace BHAS::Entities {

  PushButton::PushButton(uint8_t id, EventQueue& queue, PinName pin)
    : Entity(id), _queue(queue), _button(pin) {

    _button.fall(callback(this, &PushButton::falling_edge));
    _button.rise(callback(this, &PushButton::rising_edge));
  }

  void PushButton::on_short_press(Callback<void(BHAS::Events::EventContext&, PressType)> eventCallback) {
    _onShortPress = eventCallback;
  }

  void PushButton::on_long_press(Callback<void(BHAS::Events::EventContext&, PressType)> eventCallback) {
    _onLongPress = eventCallback;
  }

  void PushButton::falling_edge() {
    // This is ISR !
    _timer.start();
  }

  void PushButton::rising_edge() {
    // This is ISR !
    _timer.stop();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(_timer.elapsed_time()).count();
    _timer.reset();

    PressType type = (milliseconds <= MBED_CONF_BHAS_PUSH_BUTTON_SHORT_PRESS_THRESHOLD_MS ? PressType::SHORT : PressType::LONG);
    _queue.call(callback(this, &PushButton::notify_press), type);   // Currently in ISR context ! Need to move to event queue
  }

  void PushButton::notify_press(PressType type) {
    BHAS::Events::EventContext context(*this);

    if (type == PressType::SHORT && _onShortPress) _onShortPress.call(context, type);
    else if (type == PressType::LONG && _onLongPress) _onLongPress.call(context, type);
  }

};
