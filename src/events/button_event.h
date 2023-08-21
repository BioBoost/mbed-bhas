#pragma once

#include "event.h"

namespace BHAS::Events {

  // Event that contains button/touch action

  class ButtonEvent : public Event {

    public:
      enum class Type { DOWN, UP, SHORT_PRESS, LONG_PRESS };

    public:
      ButtonEvent(BHAS::Entities::Entity& entity, Type type)
        : Event(entity), _type(type) {

      }
    
    public:
      Type type() {
        return _type;
      }

    public:
      virtual std::string to_string() override {
        std::string output = "[ButtonEvent] type = ";
        switch(_type) {
          case Type::DOWN:          output += "DOWN"; break;
          case Type::UP:            output += "UP"; break;
          case Type::SHORT_PRESS:   output += "SHORT_PRESS"; break;
          case Type::LONG_PRESS:    output += "LONG_PRESS"; break;
        }
        return output;
      }

    private:
      Type _type;

  };

};