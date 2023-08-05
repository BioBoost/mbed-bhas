#pragma once

#include <stdint.h>
#include <stddef.h>
#include <cstring>
#include "message.h"
#include "InterfaceCAN.h"

namespace BHAS::Communication::Encoders {

  class CANEncoder {

    public:
      static const size_t MAX_CAN_PACKET_SIZE = 8;

    public:
      static CANMessage message_to_mbed_can_message(const Message& message) {
        char buffer[MAX_CAN_PACKET_SIZE] = { 0 };
        buffer[0] = message.source_id();
        buffer[1] = message.entity_id();
        buffer[2] = static_cast<char>(message.type());
        memcpy(buffer+3, message.payload(), message.payload_size());

        return CANMessage(message.destination_id(), buffer, 3+message.payload_size());
      }
      static Message mbed_can_message_to_message(const CANMessage& mbedMessage) {
        Message message;
        
        message.source_id(mbedMessage.id);
        message.destination_id(mbedMessage.data[0]);
        message.entity_id(mbedMessage.data[1]);
        message.type(static_cast<Message::Type>(mbedMessage.data[2]));

        return message;
      }

  };

};