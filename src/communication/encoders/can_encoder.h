#pragma once

#include <stdint.h>
#include <stddef.h>
#include <cstring>
#include "../message.h"
#include "InterfaceCAN.h"

namespace BHAS::Communication::Encoders {

  class CANEncoder {

    public:
      static const size_t MAX_CAN_PACKET_SIZE = 8;

    // CAN Message format:
    // | CAN ID (11 bits = DST) | SRC ID (8 bits) | ENT ID (8 bits) | BASE TYPE (4 bits) + SUBTYPE (4 bits) | DATA (max 5 bytes) |

    public:
      static CANMessage message_to_mbed_can_message(const Message& message) {
        char buffer[MAX_CAN_PACKET_SIZE] = { 0 };
        buffer[0] = message.source_id();
        buffer[1] = message.entity_id();
        buffer[2] = (static_cast<char>(message.base_type())  << 4) | (message.sub_type() & 0x0F);
        memcpy(buffer+3, message.payload(), message.payload_size());

        return CANMessage(message.destination_id(), buffer, 3+message.payload_size());
      }

      static Message mbed_can_message_to_message(const CANMessage& canMessage) {
        Message message;
        
        message.source_id(canMessage.data[0]);
        message.destination_id(canMessage.id);
        message.entity_id(canMessage.data[1]);
        message.base_type(static_cast<Message::BaseType>((canMessage.data[2] >> 4) & 0x0F));
        message.sub_type(canMessage.data[2] & 0x0F);
        message.payload(canMessage.data+3, canMessage.len-3);

        return message;
      }

  };

};