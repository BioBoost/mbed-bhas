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

  std::string Entity::to_string() const {
    return "Entity [id: " + std::to_string(_id) + "]" + (_description != "" ? " " + _description : "");
  }

};