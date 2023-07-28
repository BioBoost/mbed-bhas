#pragma once

#include "entity.h"
#include <stdint.h>
#include <vector>

namespace BHAS {

  class EntityManager {

    public:
      void add(Entities::Entity* entity);

    public:
      Entities::Entity* find_by_id(uint8_t id);

    private:
      std::vector<Entities::Entity*> _entities;

  };

};