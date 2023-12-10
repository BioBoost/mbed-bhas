#pragma once
#include "../../bhas_platform.h"

#include <cstdint>
#include <stddef.h>
#include <cstring>
#include "../message.h"

#if defined(PLATFORM_ESP)
#include "driver/twai.h"
#endif

namespace BHAS::Communication::Encoders {

  class CANEncoder {

    public:
      static const size_t MAX_CAN_PACKET_SIZE = 8;

    // CAN Message format:
    // | CAN ID (11 bits = DST) | SRC ID (8 bits) | ENT ID (8 bits) | BASE TYPE (4 bits) + SUBTYPE (4 bits) | DATA (max 5 bytes) |

#if defined(PLATFORM_MBED)
    public:
      static CANMessage message_to_can_message(const Message& message) {
        char buffer[MAX_CAN_PACKET_SIZE] = { 0 };
        buffer[0] = message.source_id();
        buffer[1] = message.entity_id();
        buffer[2] = (static_cast<char>(message.base_type())  << 4) | (message.sub_type() & 0x0F);
        memcpy(buffer+3, message.payload(), message.payload_size());

        return CANMessage(message.destination_id(), buffer, 3+message.payload_size());
      }

      static Message can_message_to_message(const CANMessage& canMessage) {
        Message message;
        
        message.source_id(canMessage.data[0]);
        message.destination_id(canMessage.id);
        message.entity_id(canMessage.data[1]);
        message.base_type(static_cast<Message::BaseType>((canMessage.data[2] >> 4) & 0x0F));
        message.sub_type(canMessage.data[2] & 0x0F);
        message.payload(canMessage.data+3, canMessage.len-3);

        return message;
      }
#endif

#if defined(PLATFORM_ESP)
    public:
      static twai_message_t message_to_can_message(const Message& message) {
        twai_message_t canMessage;
        canMessage.identifier = message.destination_id();
        canMessage.extd = 0;
        canMessage.data_length_code = message.payload_size() + 3;      // +3 for Sid, Eid and type
        canMessage.data[0] = message.source_id();
        canMessage.data[1] = message.entity_id();
        canMessage.data[2] = (static_cast<char>(message.base_type())  << 4) | (message.sub_type() & 0x0F);
        memcpy(canMessage.data+3, message.payload(), message.payload_size());

        return canMessage;
      }

      static Message can_message_to_message(const twai_message_t& canMessage) {
        Message message;
        
        message.source_id(canMessage.data[0]);
        message.destination_id(canMessage.identifier);
        message.entity_id(canMessage.data[1]);
        message.base_type(static_cast<Message::BaseType>((canMessage.data[2] >> 4) & 0x0F));
        message.sub_type(canMessage.data[2] & 0x0F);
        message.payload(canMessage.data+3, canMessage.data_length_code-3);

        return message;
      }
#endif

  };

};