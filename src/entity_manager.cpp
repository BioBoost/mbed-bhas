#include "entity_manager.h"

namespace BHAS {

  void EntityManager::add(Entities::Entity* entity) {
    if(find_by_id(entity->id())) {
      // Already exists !
      // TODO: Generate error
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