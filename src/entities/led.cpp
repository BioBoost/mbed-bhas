#include "led.h"

namespace BHAS::Entities {

  Led::Led(uint8_t id, PinName pin, std::string description)
    : Entity(id, description), _led(pin) {
  }

  void Led::on() {
    _led = true;
  }

  void Led::off() {
    _led = false;
  }

  void Led::toggle() {
    _led = !_led;
  }

  std::string Led::name() const {
    return "Led";
  }

  void Led::process_action(Actions::Action& action) {
    Entity::process_action(action);
    if (action.status() != Actions::Action::Status::UNHANDLED) return;

    if (action.arguments().size() != 1) {
      action.status(Actions::Action::Status::INVALID_ARGUMENT_COUNT);
      return;
    };

    LedAction command = static_cast<LedAction>(action.arguments()[0]);

    switch(command) {
      case LedAction::TURN_ON:    on();     action.status(Actions::Action::Status::SUCCESS); return;
      case LedAction::TURN_OFF:   off();    action.status(Actions::Action::Status::SUCCESS); return;
      case LedAction::TOGGLE:     toggle(); action.status(Actions::Action::Status::SUCCESS); return;
    }
  }

};
