#include "entity.h"

namespace BHAS::Entities {

  Entity::Entity(uint8_t id)
    : _id(id) {

  }

  uint8_t Entity::id() const {
    return _id;
  }

};