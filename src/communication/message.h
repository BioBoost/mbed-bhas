#pragma once

#include <stdint.h>
#include <stddef.h>

namespace BHAS::Communication {

  class Message {

    public:
      enum class BaseType : uint8_t {
        EVENT       = 0x01,
        ACTION      = 0x02,
        CONFIG      = 0x03
        // Warning, error, ... ?
      };

    public:
      Message();
      Message(uint8_t sourceId, uint8_t destinationId, uint8_t entityId, Message::BaseType baseType, uint8_t subType = 0x00);

    public:
      void source_id(uint8_t id);
      void destination_id(uint8_t id);
      void entity_id(uint8_t id);
      void base_type(Message::BaseType baseType);
      void sub_type(uint8_t subType);
      void payload(const uint8_t * payload, size_t size);

    public:
      uint8_t source_id() const;
      uint8_t destination_id() const;
      uint8_t entity_id() const;
      Message::BaseType base_type() const;
      uint8_t sub_type() const;
      const uint8_t * payload() const;
      size_t payload_size() const;

    private:
      uint8_t _sourceId = 0;
      uint8_t _destinationId = 0;
      uint8_t _entityId = 0;
      Message::BaseType _baseType;
      uint8_t _subType = 0x00;        // Subtype is specific to action, event, ... Examples: PERIODIC::ALIVE, ACTION::RESET

      static const size_t MAX_PAYLOAD_SIZE = MBED_CONF_BHAS_MAX_MESSAGE_PAYLOAD_SIZE;

      uint8_t _payload[MAX_PAYLOAD_SIZE] = { 0 };
      size_t _payloadSize = 0;

  };

};