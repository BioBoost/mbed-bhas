#pragma once

#include "entity_event.h"

namespace BHAS {

  class EntityEventHandler {

    public:
      virtual void handle_event(EntityEvent event) = 0;

  };

};