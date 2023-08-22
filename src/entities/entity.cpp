#include "entity.h"

namespace BHAS::Entities {

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
    return name() + " [id: " + std::to_string(_id) + "]" + (_description != "" ? " " + _description : "");
  }

  void Entity::process_action(Actions::Action& action) {
    switch(action.type()) {
      case Actions::Action::Type::DISABLE:    this->disable();  action.status(Actions::Action::Status::SUCCESS); break;
      case Actions::Action::Type::ENABLE:     this->enable();   action.status(Actions::Action::Status::SUCCESS); break;
      case Actions::Action::Type::RESET:      this->reset();    action.status(Actions::Action::Status::SUCCESS); break;
    }
  };

};