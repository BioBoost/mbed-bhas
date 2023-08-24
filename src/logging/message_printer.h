#pragma once

#include <cstdio>
#include "../communication/message.h"
#include "../helpers/string_convertor.h"

namespace BHAS::Logging {

  class MessagePrinter {

    public:
      static void print(char* buffer, const Communication::Message& message) {
        size_t offset = sprintf(
          buffer,
          "[Nid: %d] => [Nid: %d] (Eid: %d) _%s::%s_ | Data: ",
          message.source_id(),
          message.destination_id(),
          message.entity_id(),
          StringConvertor::message_base_type_as_string(message.base_type()).c_str(),
          StringConvertor::message_sub_type_as_string(message).c_str()
        );
        
        for (size_t i = 0; i < message.payload_size(); i++) {
          offset += sprintf(buffer+offset, "%d ", message.payload()[i]);
        }

        sprintf(buffer+offset, "{ %d byte(s) }", message.payload_size());
      }

  };

};