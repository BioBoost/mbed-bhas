#pragma once

#include "entity.h"
#include <vector>

namespace BHAS {

  class Action {

    public:
      enum class Type {
        ENTITY_ACTION = 0x00,
        // For base class Entity
        RESET         = 0x01,
        ENABLE        = 0x02,
        DISABLE       = 0x03
      };

      enum class Status {
        SUCCESS,
        UNHANDLED,
        INVALID_ARGUMENT_COUNT,
        UNSUPPORTED_ARGUMENTS
      };

    public:
      Action(Type type, std::vector<uint8_t> arguments)
        : _arguments(arguments), _type(type) {

      }
    
    public:
      std::vector<uint8_t> arguments() {
        return _arguments;
      }

      Type type() {
        return _type;
      }

      Status status() {
        return _status;
      }

    public:
      void status(Status status) {
        _status = status;
      }

    public:
      virtual std::string to_string() {
        return "[Action] ...";
      }

    private:
      std::vector<uint8_t> _arguments;
      Type _type;
      Status _status = Status::UNHANDLED;

  };

};