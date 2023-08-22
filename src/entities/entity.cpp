#include "entity.h"

namespace BHAS {

  Entity::Entity(uint8_t id, std::string description)
    : _id(id), _description(description) {

  }

  uint8_t Entity::id() const {
    return _id;
  }

  std::string Entity::description() const {
    return _description;
  }

  std::string Entity::name() const {
    return "Entity";
  }

  std::string Entity::to_string() const {
    return name() + " [Eid: " + std::to_string(_id) + "]" + (_description != "" ? " " + _description : "");
  }

  void Entity::process_action(Action& action) {
    switch(action.type()) {
      case Action::Type::DISABLE:    this->disable();  action.status(Action::Status::SUCCESS); break;
      case Action::Type::ENABLE:     this->enable();   action.status(Action::Status::SUCCESS); break;
      case Action::Type::RESET:      this->reset();    action.status(Action::Status::SUCCESS); break;
    }
  };

  void Entity::on_event(mbed::Callback<void(Event&)> eventCallback) {
    _onEvent = eventCallback;
  }

  void Entity::call_event_handler(Event& event) {
    if (_onEvent) {
      _onEvent.call(event);
    }
  }

};