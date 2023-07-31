#include "entity_manager.h"
#include "mbed_trace.h"

#define TRACE_GROUP "BHAS EntityManager"

namespace BHAS {

  void EntityManager::add(Entities::Entity* entity) {
    if(find_by_id(entity->id())) {
      tr_error("Entity with id = [%d] already registered", entity->id());
      return;
    }
    _entities.push_back(entity);
  }

  Entities::Entity* EntityManager::find_by_id(uint8_t id) {
    for(Entities::Entity* entity : _entities) {
      if (entity->id() == id) return entity;
    }
    return nullptr;
  }

};