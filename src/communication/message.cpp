#include "message.h"
#include <cstring>
#include <algorithm>

namespace BHAS::Communication {

  const size_t Message::MAX_PAYLOAD_SIZE;     // Definition

  Message::Message() { }

  Message::Message(uint8_t sourceId, uint8_t destinationId, uint8_t entityId, Message::BaseType baseType, uint8_t subType) {
    source_id(sourceId);
    destination_id(destinationId);
    entity_id(entityId);
    base_type(baseType);
    sub_type(subType);
  }

  void Message::source_id(uint8_t id) {
    _sourceId = id;
  }

  void Message::destination_id(uint8_t id) {
    _destinationId = id;
  }

  void Message::entity_id(uint8_t id) {
    _entityId = id;
  }

  void Message::base_type(Message::BaseType baseType) {
    _baseType = baseType;
  }

  void Message::sub_type(uint8_t subType) {
    _subType = subType;
  }

  void Message::payload(const uint8_t * payload, size_t size) {
    size = std::min(size, MAX_PAYLOAD_SIZE);    // If payload is to big we truncate
    memcpy(_payload, payload, size);
    _payloadSize = size;
  }

  uint8_t Message::source_id() const {
    return _sourceId;
  }

  uint8_t Message::destination_id() const {
    return _destinationId;
  }

  uint8_t Message::entity_id() const {
    return _entityId;
  }

  Message::BaseType Message::base_type() const {
    return _baseType;
  }

  uint8_t Message::sub_type() const {
    return _subType;
  }

  const uint8_t * Message::payload() const {
    return _payload;
  }

  size_t Message::payload_size() const {
    return _payloadSize;
  }

};