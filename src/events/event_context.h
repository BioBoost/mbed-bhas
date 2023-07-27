#pragma once

#include "entity.h"

namespace BHAS::Events {

  class EventContext {

    public:
      EventContext(BHAS::Entities::Entity& entity)
        : _entity(entity) {

      }
    
    public:
      BHAS::Entities::Entity& entity() {
        return _entity;
      }

    private:
      BHAS::Entities::Entity& _entity;

  };

};