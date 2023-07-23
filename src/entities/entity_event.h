#pragma once

#include <stdint.h>
#include "entity.h"

namespace BHAS {

  class EntityEvent {

    public:
      enum class EventType {
        NONE,
        SHORT_PRESS,
        LONG_PRESS,
      };

    public:
      EntityEvent(Entity * entity, EventType type)
        : _entity(entity), _type(type) {
      }

    public:
      Entity * entity() const {
        return _entity;
      }

      EventType type() const {
        return _type;
      }

    private:
      Entity * _entity = nullptr;
      EventType _type = EventType::NONE;

  };

};