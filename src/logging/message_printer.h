#pragma once

#include "../communication/message.h"
#include <cstdio>

namespace BHAS {

  class MessagePrinter {

    public:
      static void print(char * buffer, Message * message) {
        size_t offset = sprintf(
          buffer,
          "[%d] => [%d] (Ent. ID: %d) _%s_ | Data: ",
          message->source_id(),
          message->destination_id(),
          message->entity_id(),
          message_type_as_string(message->type())
        );
        
        for (size_t i = 0; i < message->payload_size(); i++) {
          offset += sprintf(buffer+offset, "%d ", message->payload()[i]);
        }

        sprintf(buffer+offset, "{ %d bytes }", message->payload_size());
      }

      static char * message_type_as_string(Message::Type type) {
        switch(type) {
          case Message::Type::NONE: return "NONE";
          case Message::Type::HELLO: return "HELLO";
          case Message::Type::EVENT: return "EVENT";
          case Message::Type::ALERT: return "ALERT";
          case Message::Type::CONFIG: return "CONFIG";
          case Message::Type::PERIOD: return "PERIOD";
          case Message::Type::WARNING: return "WARNING";
          case Message::Type::ERROR: return "ERROR";
          case Message::Type::ALIVE: return "ALIVE";
          default: return "?????";
        }
      }

  };

};