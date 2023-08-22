#pragma once

#include "message.h"
#include <cstdio>
#include <string>
#include "../entities/events/event.h"
#include "../entities/actions/action.h"

namespace BHAS::Logging {

  class MessagePrinter {

    public:
      static void print(char* buffer, const Communication::Message& message) {
        std::string subType = "";
        if (message.base_type() == Communication::Message::BaseType::EVENT) {
          subType = event_type_as_string(static_cast<Event::Type>(message.sub_type()));
        } else if (message.base_type() == Communication::Message::BaseType::ACTION) {
          subType = action_type_as_string(static_cast<Action::Type>(message.sub_type()));
        }

        size_t offset = sprintf(
          buffer,
          "[Nid: %d] => [Nid: %d] (Eid: %d) _%s::%s_ | Data: ",
          message.source_id(),
          message.destination_id(),
          message.entity_id(),
          message_type_as_string(message.base_type()).c_str(),
          subType.c_str()
        );
        
        for (size_t i = 0; i < message.payload_size(); i++) {
          offset += sprintf(buffer+offset, "%d ", message.payload()[i]);
        }

        sprintf(buffer+offset, "{ %d byte(s) }", message.payload_size());
      }

      static std::string message_type_as_string(Communication::Message::BaseType type) {
        using Communication::Message;
        switch(type) {
          case Message::BaseType::EVENT:    return "EVENT";
          case Message::BaseType::CONFIG:   return "CONFIG";
          case Message::BaseType::ACTION:   return "ACTION";
          default: return "UNKNOWN";
        }
      }

      static std::string event_type_as_string(Event::Type type) {
        switch(type) {
          case Event::Type::ALIVE:        return "ALIVE";
          case Event::Type::BOOT:         return "BOOT";
          case Event::Type::BUTTON:       return "BUTTON";
          case Event::Type::TEMPERATURE:  return "TEMPERATURE";
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

  };

};