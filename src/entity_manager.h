#pragma once

#include "entity.h"
#include <stdint.h>
#include <vector>

namespace BHAS {

  class EntityManager {

    public:
      void add(Entity* entity);

    public:
      Entity* find_by_id(uint8_t id);
      uint8_t get_free_id();

    private:
      std::vector<Entity*> _entities;

  };

};