#pragma once

#include <string>
#include "../communication/message.h"
#include "../entities/events/event.h"
#include "../entities/actions/action.h"

namespace BHAS {

  class StringConvertor {

    public:
      static std::string event_type_as_string(Event::Type type) {
        switch(type) {
          case Event::Type::ALIVE:          return "ALIVE";
          case Event::Type::BOOT:           return "BOOT";
          case Event::Type::BUTTON:         return "BUTTON";
          case Event::Type::TEMPERATURE:    return "TEMPERATURE";
          case Event::Type::CHANNEL_STATS:  return "CHANNEL_STATS";
          default: return "UNKNOWN";
        }
      }

      static std::string action_type_as_string(Action::Type type) {
        switch(type) {
          case Action::Type::ENTITY_ACTION: return "ENTITY_ACTION";
          case Action::Type::DISABLE:       return "DISABLE";
          case Action::Type::ENABLE:        return "ENABLE";
          case Action::Type::RESET:         return "RESET";
          default: return "UNKNOWN";
        }
      }

      static std::string message_base_type_as_string(Communication::Message::BaseType type) {
        using Communication::Message;

        switch(type) {
          case Message::BaseType::EVENT:    return "EVENT";
          case Message::BaseType::CONFIG:   return "CONFIG";
          case Message::BaseType::ACTION:   return "ACTION";
          default: return "UNKNOWN";
        }
      }

      static std::string message_sub_type_as_string(const Communication::Message& message) {
        using Communication::Message;
        std::string subType = "UNKNOWN";

        if (message.base_type() == Message::BaseType::EVENT) {
          subType = StringConvertor::event_type_as_string(static_cast<Event::Type>(message.sub_type()));
        } else if (message.base_type() == Message::BaseType::ACTION) {
          subType = StringConvertor::action_type_as_string(static_cast<Action::Type>(message.sub_type()));
        }

        return subType;
      }

  };

};
