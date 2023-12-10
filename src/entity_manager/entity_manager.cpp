#include "../bhas_platform.h"
#include "../logging/trace_logging.h"
#include "entity_manager.h"

#define TRACE_GROUP "BHAS EntityManager"

namespace BHAS {

  void EntityManager::add(Entity* entity) {
    if(find_by_id(entity->id())) {
      tr_error("Entity with id = [%d] already registered", entity->id());
      return;
    }
    _entities.push_back(entity);
  }

  Entity* EntityManager::find_by_id(uint8_t id) {
    for(Entity* entity : _entities) {
      if (entity->id() == id) return entity;
    }
    return nullptr;
  }

  uint8_t EntityManager::get_free_id() {
    for (uint16_t id = 0; id < 256; id++) {   // 16 bit so we can detect overflow
      uint8_t oneByteId = static_cast<uint8_t>(id);
      if (find_by_id(oneByteId) == nullptr) return oneByteId;
    }

    tr_error("No free entity ID left");
    return 255;     // Never gonna happen
  }

};