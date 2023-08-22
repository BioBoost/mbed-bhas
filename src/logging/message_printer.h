#pragma once

#include "message.h"
#include <cstdio>

namespace BHAS::Logging {

  class MessagePrinter {

    public:
      static void print(char* buffer, const Communication::Message& message) {
        size_t offset = sprintf(
          buffer,
          "[%d] => [%d] (Ent. ID: %d) _%s::%d_ | Data: ",
          message.source_id(),
          message.destination_id(),
          message.entity_id(),
          message_type_as_string(message.base_type()),
          message.sub_type()
        );
        
        for (size_t i = 0; i < message.payload_size(); i++) {
          offset += sprintf(buffer+offset, "%d ", message.payload()[i]);
        }

        sprintf(buffer+offset, "{ %d bytes }", message.payload_size());
      }

      static const char* message_type_as_string(Communication::Message::BaseType type) {
        using Communication::Message;
        switch(type) {
          case Message::BaseType::EVENT:    return "EVENT";
          case Message::BaseType::CONFIG:   return "CONFIG";
          case Message::BaseType::ACTION:   return "ACTION";
          default: return "UNKNOWN";
        }
      }

  };

};