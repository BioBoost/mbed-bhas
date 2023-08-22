#pragma once

#include "entity.h"
#include <vector>

namespace BHAS {

  // Forward declaration
  namespace Entities { class Entity; };

  class Event {

    public:
      enum class Type {
        BOOT =          0x00,
        ALIVE =         0x01,
        BUTTON =        0x02,
        TEMPERATURE =   0x03
      };

    public:
      Event(Entities::Entity& entity, Type type, std::vector<uint8_t> arguments)
        : _entity(entity), _arguments(arguments), _type(type) {

      }
    
    public:
      Entities::Entity& entity() {
        return _entity;
      }

      std::vector<uint8_t> arguments() {
        return _arguments;
      }

      Type type() {
        return _type;
      }

    public:
      virtual std::string to_string() {
        return "[Event] ...";
      }

    private:
      Entities::Entity& _entity;
      std::vector<uint8_t> _arguments;
      Type _type;

  };

};
