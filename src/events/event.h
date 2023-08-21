#pragma once

#include "entity.h"

namespace BHAS::Events {

  // Base class for more specific events

  class Event {

    public:
      Event(BHAS::Entities::Entity& entity)
        : _entity(entity) {

      }
    
    public:
      BHAS::Entities::Entity& entity() {
        return _entity;
      }

    public:
      virtual std::string to_string() {
        return "[Event] ...";
      }

    private:
      BHAS::Entities::Entity& _entity;

  };

};