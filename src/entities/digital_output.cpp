#include "digital_output.h"

namespace BHAS::Entities {

  DigitalOutput::DigitalOutput(uint8_t id, PinName pin, std::string description)
    : Entity(id, description), _out(pin) {
  }

  void DigitalOutput::on() {
    _out = true;
  }

  void DigitalOutput::off() {
    _out = false;
  }

  void DigitalOutput::toggle() {
    _out = !_out;
  }

  std::string DigitalOutput::name() const {
    return "DigitalOutput";
  }

  void DigitalOutput::process_action(Action& action) {
    Entity::process_action(action);
    if (action.status() != Action::Status::UNHANDLED) return;

    if (action.arguments().size() != 1) {
      action.status(Action::Status::INVALID_ARGUMENT_COUNT);
      return;
    };

    OutputAction command = static_cast<OutputAction>(action.arguments()[0]);

    switch(command) {
      case OutputAction::TURN_ON:    on();     action.status(Action::Status::SUCCESS); return;
      case OutputAction::TURN_OFF:   off();    action.status(Action::Status::SUCCESS); return;
      case OutputAction::TOGGLE:     toggle(); action.status(Action::Status::SUCCESS); return;
    }
  }

};
